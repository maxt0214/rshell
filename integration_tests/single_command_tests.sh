#test case 1
echo "ls" > commands.txt

#test case 2
echo "pwd" >> commands.txt

#test case 3
echo "lsa" >> commands.txt

#test case 4
echo "mkdir hello # ls" >> commands.txt

#test case 5
echo "rmdir hello" >> commands.txt

#test case 6
echo "exit # not I exit" >> commands.txt
truncate -s-1 commands.txt

echo "-Single Command Tests-" >> result.txt
../rshell < commands.txt >> result.txt
