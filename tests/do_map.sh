RED='\033[0;31m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
END='\033[0m'

echo -e "${YELLOW}Testing ft::map and comparing to std::map${END}"
mkdir -p ./res_map
start_std=$(date +%s.%N)
g++ -g -Wall -Werror -Wextra -std=c++98 -D NS=std map_tests.cpp -o std_map.out > ./res_map/std_map.txt
end_std=$(date +%s.%N)
start_ft=$(date +%s.%N)
g++ -g -Wall -Werror -Wextra -std=c++98 -D NS=ft map_tests.cpp -o ft_map.out > ./res_map/ft_map.txt
end_ft=$(date +%s.%N)
result=$(diff -y ./res_map/std_map.txt ./res_map/ft_map.txt)

if [ $? -eq 0 ]
then
	echo -e "===> ${GREEN}NO DIFF${END}"
else
	echo -e "===> ${RED}DIFF !!!${END}"
	echo "${result}"
fi
time_std=$(echo "(${end_std} - ${start_std}) * 100000000" | bc)
time_ft=$(echo "(${end_ft} - ${start_ft}) * 100000000" | bc)
max_allowed_time_ft=$(echo "${time_std} * 20" | bc)
comp=$(echo "${time_ft} > ${max_allowed_time_ft}" | bc)
if [ ${comp} -eq 1 ]
then
	echo -e "====> ${RED}TIMEOUT${END}"
	echo "Time std: ${time_std}"
	echo "Time ft: ${time_ft}"
else
	echo -e "====> ${GREEN}TIME OK${END}"
fi
