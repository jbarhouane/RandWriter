#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class RandWriter {
 public:
RandWriter(std::string text, int k, int L);
int orderK() const;
int freq(std::string kgram) const;
int freq(std::string kgram, char c) const;
char kRand(std::string kgram);
std::string generate(std::string kgram, int L);
friend std::ostream& operator<<(std::ostream& output, RandWriter rWriter);
void init_alphabet(void);
void init_kgram(void);
void init_map_struct(void);
std::string getKgram(void);
std::string getAlphabet(void);
int k1gramcounter(void);

 private:
  std::string text;
  std::string kgram;
  std::string alphabet;
  std::unordered_map<std::string, std::vector<char>> map_struct;
  size_t k;
  int L;
};
