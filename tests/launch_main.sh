g++ -std=c++98 -Wall -Werror -Wextra -D STL=1 ./main_tests/main.cpp -o main_std
echo -e "\033[0;33mNamespace: STD (seed = 0)\033[0m"
echo -e "\033[0;33m-------------------------\033[0m"
./main_std 0
rm main_std
echo ""
g++ -std=c++98 -Wall -Werror -Wextra ./main_tests/main.cpp -o main_ft
echo -e "\033[0;33mNamespace: FT (seed = 0)\033[0m"
echo -e "\033[0;33m------------------------\033[0m"
./main_ft 0
rm main_ft
