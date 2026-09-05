#include <string>
#include <vector>

void tokenize_on_spaces(std::string &input, std::vector<std::string> &v) {
<<<<<<< HEAD
  int i = 0;
  while (i < input.length()) {
    std::string curr = "";
    while (i < input.length() && input[i] != ' ') {
      curr += input[i];
      i++;
    }
    while (i < input.length() && input[i] == ' ') {
      i++;
    }
    v.emplace_back(curr);
  }
}
=======
    int i = 0;
    while(i < input.length()) {
        std::string curr = "";
        while(i < input.length() && input[i] != ' ') {
            curr += input[i];
            i++;
        }
        i++;
        v.emplace_back(curr);
    }
}
>>>>>>> 02af3dc (Add tests and Cmake support with folder segregation)
