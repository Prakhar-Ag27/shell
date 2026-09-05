#include <string>
#include <vector>

<<<<<<< HEAD
void tokenize_on_spaces(std::string &input, std::vector<std::string> &v) {
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> b786a11 (Add tests and Cmake support with folder segregation)
  int i = 0;
  while (i < input.length()) {
    std::string curr = "";
    while (i < input.length() && input[i] != ' ') {
      curr += input[i];
      i++;
<<<<<<< HEAD
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
=======
    }
    while (i < input.length() && input[i] == ' ') {
      i++;
    }
    v.emplace_back(curr);
  }
}
>>>>>>> b786a11 (Add tests and Cmake support with folder segregation)
=======
void tokenize_on_spaces(std::string &input, std::vector<std::string> &v);
>>>>>>> 3940907 (fix odr)
