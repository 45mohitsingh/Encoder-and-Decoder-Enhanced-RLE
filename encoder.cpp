#include <bits/stdc++.h>
#include <divsufsort.h>
#include <iostream>
#include <memory>

class Encoder {

public:
  Encoder(std::string data) : m_data(data) {}

  // private:
  std::string m_data;
  std::string m_remapping;
  std::string m_bwtstring;
  int m_idx;

  std::vector<int> Encode() {
    m_data += '$';
    std::string suffixString = getBWST();
    std::vector<std::string> verticalBytes = readVerticalBytes(suffixString);
    std::vector<int> finalEncoded = runLengthEncode(verticalBytes);
    return finalEncoded;
  }

  std::string getBWST() {
    int len = m_data.length();
    int *SA = new int[len * sizeof(int)];
    const char *Text = m_data.c_str();
    char *buf = new char[len];

    divsufsort((unsigned char *)Text, SA, len);

    std::string result = "";
    for (int i = 0; i < len; ++i) {
      if(SA[i] == 0) m_idx = i;
      result += m_data[(SA[i] + len - 1) % len];
    }
    m_bwtstring = result;
    return result;
  }

  std::map<char, int> dynamicByteRemapping(const std::string &data) {

    std::map<char, int> mp;
    for (auto el : data) {
      mp[el]++;
    }
    std::vector<std::pair<int, char>> result;
    for (auto el : mp) {
      result.push_back({el.second, el.first});
    }
    sort(result.rbegin(), result.rend(),
         [](std::pair<int, char> &a, std::pair<int, char> &b) {
           if (a.first != b.first)
             return a.first < b.first;
           else
             return a.second > b.second;
         });

    std::map<char, int> order;
    int cur = 0;
    for (auto el : result) {
      order[el.second] = cur++;
    }
    for (auto el : result) {
      m_remapping += el.second;
    }
    return order;
  }

  std::vector<std::string> readVerticalBytes(const std::string &data) {

    std::map<char, int> remapping = dynamicByteRemapping(data);
    const int numOfBits = 8;
    std::vector<std::string> result(numOfBits);
    int len = data.length();
    for (int i = 0; i < numOfBits; i++) {
      for (int j = 0; j < len; j++) {
        int cur = remapping[data[j]];
        result[i] += ((cur >> i) & 1) + '0';
      }
    }

    return result;
  }

  std::vector<int> runLengthEncode(std::vector<std::string> &data) {

      int cnt =0;
      int cur = 0;
      int mx = 255;
      std::vector<int> result;
      for (int i = 7; i >= 0; i--) {
          for (int j = 0; j < data[i].size(); j++) {
              if (data[i][j] - '0' == cur) {
                  cnt++;
              } else {
                 // while(cnt > mx) {
                  //    result.push_back(mx);
                 //     result.push_back(0);
                  //    cnt -= mx;
                  //}
                  //  if(cnt > 0) 
                  result.push_back(cnt);
                  cur ^= 1;
                  cnt = 1;
              }
          }
      }
      result.push_back(cnt);
      return result;
  }
};

int main(int argc, char* argv[]) {
  std::ifstream inFile(argv[1]);
  std::ofstream outFile("output.txt");

  std::stringstream buffer;
  buffer << inFile.rdbuf();

  std::cerr<<"Reading File " << argv[1]<<"\n";
  std::string text = buffer.str();

  Encoder *e = new Encoder(text);

  std::vector<int> encodedText = e->Encode();

  for (auto el : encodedText) {
      outFile << el << " ";
  }
  outFile << "\n";
  outFile << e->m_idx << "\n";
  outFile << e->m_remapping;
  std::cout<<"File Successfully encoded! (->output.txt)";
}

