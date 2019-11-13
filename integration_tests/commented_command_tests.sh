#test case 1
echo "ls # lsa || pwd" > commands.txt

#test case 2
echo "pwd # lsa || pwd" >> commands.txt

#test case 3
echo "lsa # lsa ; pwd" >> commands.txt

#test case 4
echo "# ls && pwd" >> commands.txt

#test case 5
echo "echo this should be printed out # echo this should not be printed out" >> commands.txt

#test case 6
echo "exit # not I exit" >> commands.txt
truncate -s-1 commands.txt

echo "-Commented Command Tests-" >> result.txt
../rshell < commands.txt >> result.txt