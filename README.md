# Enhanced Run Length Encoding (RLE) Compression

This project implements an advanced approach to improve the efficiency of Run Length Encoding (RLE) by combining several preprocessing techniques. These enhancements aim to transform the input data into a form that is more suitable for RLE compression, and also integrate Huffman Encoding to further optimize the compression performance.

## Introduction

Run Length Encoding (RLE) is widely used for lossless compression due to its simplicity. It works effectively on data that contains long sequences of repeating symbols. However, for natural text and other data with short sequences of repeated symbols, its efficiency is limited. This project proposes a method that enhances RLE by applying the following preprocessing techniques:

- **Vertical Byte Reading**
- **Dynamic Byte Remapping**
- **Burrows-Wheeler-Scott (BWS) Transform**

By preprocessing the input data into a more RLE-friendly format and then applying Huffman Encoding, this method offers significant improvements over traditional RLE.

## Features

- Preprocessing techniques to optimize input data for compression.
- Combines Run Length Encoding (RLE) with Huffman Encoding for better compression.
- Easy-to-use encoding and decoding processes.

## Requirements

This project requires the **LdivSufSort** library, which can be found on the [LdivSufSort GitHub page](https://github.com/y-256/libdivsufsort).

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/45mohitsingh/Encoder-and-Decoder-Enhanced-RLE.git
   ```
2. Install **LdivSufSort**:
   - On Linux:
     ```bash
     sudo apt-get install libdivsufsort-dev
     ```
   - On Windows, you can use `vcpkg`:
     ```bash
     vcpkg install divsufsort
     vcpkg integrate install
     ```

## Building the Project

### Encoding

1. Compile the `encoder.cpp` file:
   ```bash
   g++ encoder.cpp -ldivsubsort -o encoder
   ```
2. Run the encoder:
   ```bash
   ./encoder {file-name}
   ```
   This will compress the specified `{file-name}` and create the compressed output file `output.txt`.

### Decoding

1. Compile the `decoder.cpp` file:
   ```bash
   g++ decoder.cpp -o decoder
   ```
2. Run the decoder:
   ```bash
   ./decoder {file-name}
   ```
   This will decompress the specified `{file-name}` and create the decoded output file `final.txt`.

## Conclusion

The project showcases the potential of combining advanced preprocessing techniques with RLE to improve compression performance. While Huffman encoding was skipped in certain tests, the improvements in run lengths validate the proposed methodology.
