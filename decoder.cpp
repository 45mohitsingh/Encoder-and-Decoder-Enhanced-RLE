#include <bits/stdc++.h>
using namespace std;
class Decoder
{
public:
    int total_bit_count = 0;
    int total_char = 0;
    void cal_element(vector<int> &incoded_rle)
    {
        for (int i = 0; i < incoded_rle.size(); i++)
        {
            total_bit_count += incoded_rle[i];
        }

        total_char = total_bit_count / 8;
        //   cout<<total_char<<endl;
    }
    void decode(vector<int> &incoded_rle, string &alphabets, int &index)
    {
        // cout<<"decode"<<endl;
        vector<int> elements(total_char, 0);
        int bit_pos = 7, k = 0;
        for (int i = 0; i < incoded_rle.size(); i++)
        {
            int bit_length = incoded_rle[i];
            while (bit_length)
            {
                elements[k] = ((i % 2) << bit_pos) | elements[k];
                k = (k + 1) % total_char;
                if (k == 0)
                    bit_pos--;
                bit_length--;
            }
        }
        //   cout<<elements[0]<<" "<<elements[1]<<endl;
        string str = "";
        for (int i = 0; i < elements.size(); i++)
        {
            str += alphabets[elements[i]];
        }

        // ciginal.end());
        std::string original = invert(str, index);
        original.pop_back();
        ofstream out("final.txt");
        out << original;
    }

    string invert(string bwtArr, int x)
    {
        int lenBwt = bwtArr.length();
        string sortedBwt = bwtArr;
        sort(sortedBwt.begin(), sortedBwt.end());
        int *lShift = new int[lenBwt];

        vector<int> *arr = new vector<int>[128];

        for (int i = 0; i < lenBwt; i++)
        {
            arr[bwtArr[i]].push_back(i);
        }

        for (int i = 0; i < lenBwt; i++)
        {
            lShift[i] = arr[sortedBwt[i]][0];
            arr[sortedBwt[i]].erase(arr[sortedBwt[i]].begin());
        }

        // Decodes the bwt
        char *decoded = new char[lenBwt];
        for (int i = 0; i < lenBwt; i++)
        {
            x = lShift[x];
            decoded[lenBwt - 1 - i] = bwtArr[x];
        }
        string decodedStr(decoded, lenBwt);

        return string(decodedStr.rbegin(), decodedStr.rend());
    }
};

string read_second_line()
{
    std::ifstream file("output.txt");
    std::string line;
    std::string content;

    // Skip the first line
    std::getline(file, line);
    std::getline(file, line); // Skip second line

    // Read from line number 2 to the end of the file
    while (std::getline(file, line))
    {
        content += line + "\n";
    }

    file.close();

    return content;
}

void readFile(vector<int> &incoded_data, int &index, char* argv[])
{
    fstream newfile;

    vector<int> series_of_integers;
    int single_integer;

    newfile.open(argv[1], ios::in);

    if (newfile.is_open())
    {
        string first_line, second_line;

        getline(newfile, first_line);

        stringstream ss_first(first_line);

        int temp;
        while (ss_first >> temp)
        {
            series_of_integers.push_back(temp);
        }

        getline(newfile, second_line);

        stringstream ss_second(second_line);
        ss_second >> single_integer;

        newfile.close();
    }

    incoded_data = series_of_integers;
    index = single_integer;
}
int main(int argc, char* argv[])
{
    vector<int> incoded_data;

    string characters;
    int index = 0;
    std::cout<<"Reading File " << argv[1]<<"\n";
    readFile(incoded_data, index, argv);
    characters = read_second_line();

    Decoder hello;
    hello.cal_element(incoded_data);
    hello.decode(incoded_data, characters, index);
    std::cout << "File decoded in final.txt" << endl;
    return 0;
}
