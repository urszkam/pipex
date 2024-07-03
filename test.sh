#!/bin/bash
grn=$'\e[1;32m'
red=$'\e[1;31m'
yel=$'\e[0;33m'
blu=$'\e[0;34m'
pur=$'\e[0;35m'
wit=$'\e[0;37m'
gre_2=$'\e[38;5;35m'
input="example.txt"
output="pipe/output_m"
output_b="pipe/output_b"
output_here="pipe/here_doc_out"
path_std="test_std/test_m"
path_bon="test_std/test_b"
here_doc="test_std/here_doc"
echo "${yel}========================= ${pur}PIPEX TESTER ${yel}========================="


#test 1
echo "${gre_2}mandatory part :"
./pipex "$input" "cat" "grep name" "$output"1 &&  cat "$input" | grep "name" > "$path_std"1 ;
if [[ $(diff --brief <(sort "$output"1) <(sort "$path_std"1)) ]] ; then
	echo "${red}1. KO${yel}"
else
	echo "${grn}1. OK${yel}"
fi
sleep 0.3
#test 2
./pipex "$input" "grep -i a" "grep -E e$" "$output"2 &&  cat "$input" | grep -i a | grep -E e$ > "$path_std"2;
if [[ $(diff --brief <(sort "$output"2) <(sort "$path_std"2)) ]] ; then
	echo "${red}2. KO${yel}"
else
	echo "${grn}2. OK${yel}"
fi
sleep 0.3
test 3
./pipex "$input" "grep -i s" "sort" "$output"3 && cat "$input" | grep -i s | sort > "$path_std"3;
if [[ $(diff --brief <(sort "$output"3) <(sort "$path_std"3)) ]] ; then
	echo "${red}3. KO${yel}"
else
	echo "${grn}3. OK${yel}"
fi
sleep 0.3
#test 4
./pipex "$input" "grep -i s" "wc -l" "$output"4 && cat "$input" | grep -i s | wc -l > "$path_std"4;
if [[ $(diff --brief <(sort "$output"4) <(sort "$path_std"4)) ]] ; then
	echo "${red}4. KO${yel}"
else
	echo "${grn}4. OK${yel}"
fi
sleep 0.3
#test 5
./pipex "$input" "ls -l ../" "wc -l" "$output"5 && ls -l ../ | wc -l > "$path_std"5;
if [[ $(diff --brief <(sort "$output"5) <(sort "$path_std"5)) ]] ; then
	echo "${red}5. KO${yel}"
else
	echo "${grn}5. OK${yel}"
fi
for i in {1..5} ;do rm -f "$output"$i rm -f "$path_std"$i ; done


echo "${gre_2}bonus part multiple pipes :"
#test 1
chmod 000 "$input"
./pipex "$input" "cat" "grep name" "grep -E a$" "wc -l" "$output_b"1 && cat "$input" | grep name | grep -E a$ | wc -l > "$path_bon"1;
if [[ $(diff --brief <(sort "$output_b"1) <(sort "$path_bon"1)) ]] ; then
	echo "${red}1. KO${yel}"
else
	echo "${grn}1. OK${yel}"
fi
sleep 0.3
chmod 644 "$input"
#test 2
./pipex "$input" "cat" "grep -i a" "grep -E e$" "$output_b"2 && cat "$input" | grep -i a | grep -E e$  > "$path_bon"2;
if [[ $(diff --brief <(sort "$output_b"2) <(sort "$path_bon"2)) ]] ; then
	echo "${red}2. KO${yel}"
else
	echo "${grn}2. OK${yel}"
fi
sleep 0.3
#test 3
./pipex "$input" "cat" "gre -v a" "grep -E s$" "$output_b"3 && cat "$input" | gre -v a | grep -E s$ > "$path_bon"3; 
if [[ $(diff --brief <(sort "$output_b"3) <(sort "$path_bon"3)) ]] ; then
	echo "${red}3. KO${yel}"
else
	echo "${grn}3. OK${yel}"
fi
sleep 0.3
#test 4
./pipex "$input" "cat" "grep -i s" "sort" "head -n 3" "uniq" "tail -5" "wc -l" "$output_b"4 && cat "$input" | grep -i s | sort | head -n 3 | uniq |tail -5 | wc -l > "$path_bon"4;
if [[ $(diff --brief <(sort "$output_b"4) <(sort "$path_bon"4)) ]] ; then
	echo "${red}4. KO${yel}"
else
	echo "${grn}4. OK${yel}"
fi
sleep 0.3
#test 5
./pipex "$input" "cat" "grep -i s" "head -n 3" "sort"  "uniq" "tail -5" "$output_b"5 && cat "$input" | grep -i s | head -n 3 | sort | uniq |tail -5  > "$path_bon"5;
if [[ $(diff --brief <(sort "$output_b"5) <(sort "$path_bon"5)) ]] ; then
	echo "${red}5. KO${yel}"
else
	echo "${grn}5. OK${yel}"
fi
for i in {1..5}; do rm -f "$output_b"$i rm -f "$path_bon"$i; done


echo "${yel}============================== ${pur}END ${yel}============================="