#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <unordered_map>
#include "RandWriter.hpp"

RandWriter::RandWriter(std::string text, int k, int L) : text(text), k(k), L(L){
    init_alphabet();
    init_kgram();
    init_map_struct();
}

int RandWriter::orderK() const {
    return k;
}

void RandWriter::init_alphabet(void) {
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~\x7F\x00\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0B\x0C\r\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F";
}

void RandWriter::init_kgram(void) {
    srand(time(NULL));
    if (k > 0) {
        size_t randFirstChar = rand() % (text.length() - k);
        kgram = text.substr(randFirstChar, k);
    }
    else {
        kgram = "";
    }
}

void RandWriter::init_map_struct(void) {
    if (k > 0) {
        for (auto textScanner = text.begin(); textScanner <= text.end() - k - 1; textScanner++) {
            std::string kgram_found(textScanner, textScanner + k);
            char next_char = textScanner[k];
            map_struct[kgram_found].push_back(next_char);
        }
    }
}

std::string RandWriter::getKgram(void) {
    return kgram;
}

std::string RandWriter::getAlphabet(void) {
    return alphabet;
}

int RandWriter::freq(std::string kgram) const {
  if (kgram.length() != k) {
    throw std::invalid_argument("Sorry, the length of kgram does not match k.");
  }
  int kgramCounter = 0;
  for (auto textScanner = text.begin(); textScanner <= text.end() - k; textScanner++) {
    if (std::string(textScanner, textScanner + k) == kgram) {
      kgramCounter++;
    }
  }
  return kgramCounter;
}

int RandWriter::freq(std::string kgram, char c) const {
  if (kgram.length() != k) {
    throw std::invalid_argument("Sorry, the length of kgram does not match k.");
  }
  int kgramCounter = 0;
  for (auto textScanner = text.begin(); textScanner <= text.end() - k - 1; textScanner++) {
    if (std::string(textScanner, textScanner + k + 1) == kgram + c) {
      kgramCounter++;
    }
  }
  return kgramCounter;
}
int RandWriter::k1gramcounter() {
    int k1Counter = 0;

    for (size_t i = 0; i < text.length() - orderK() - 1; i++) {
        std::string kgram = text.substr(i, orderK());
        char next_char = text[i + orderK()];

        if (text.substr(i + 1, orderK()) == kgram + next_char) {
            k1Counter++;
        }
    }

    return k1Counter;
}



char RandWriter::kRand(std::string kgram) {
    if (kgram.length() != k) {
        throw std::invalid_argument("Sorry, the length of kgram does not match k.");
    }

    auto textScanner = map_struct.find(kgram);
    if (textScanner == map_struct.end()) {
        throw std::runtime_error("Sorry, no characters follow the given kgram.");
    }

    std::vector<char>& rChar = map_struct[kgram];

    srand(time(NULL));
    int rIndex = rand() % rChar.size();

    return rChar[rIndex];
}

std::string RandWriter::generate(std::string kgram, int L) {
    if (kgram.length() != k) {
        throw std::invalid_argument("Sorry, the length of kgram does not match k.");
    }
    if (L < orderK()) {
        throw std::invalid_argument("Sorry, the value of L must be greater than or equal to k.");
    }

    std::string genText = kgram;
    for (int i = 0; i < L - orderK(); ++i) {
        char nextChar;

        if (orderK() == 0) {
            nextChar = text[rand() % text.size()];
        }
        else {
            nextChar = kRand(kgram);
            for (size_t j = 0; j < kgram.length() - 1; ++j) {
                kgram[j] = kgram[j + 1];
            }
            kgram[kgram.length() - 1] = nextChar;
        }
        genText += nextChar;
    }

    return genText;
}

std::ostream& operator<<(std::ostream& output, RandWriter rWriter) {
    output << "Markov Order: " << rWriter.orderK() << std::endl;
    output << "Alphabet: " << rWriter.getAlphabet() << std::endl;
    output << "kgram frequency is " << rWriter.freq(rWriter.getKgram()) << std::endl;
    output << "kgram frequency plus another character is: " << std::endl;
    output << rWriter.k1gramcounter() << std::endl;
    output << rWriter.generate(rWriter.getKgram(), rWriter.L) << std::endl;
    return output;
}