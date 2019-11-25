echo "-Single Command Tests-"
echo

#test case 1
echo "ls" > commands.txt
truncate -s-1 commands.txt
echo "$ ls"
echo
../integration_test < commands.txt
echo

#test case 2
echo "pwd" > commands.txt
truncate -s-1 commands.txt
echo "$ pwd"
echo
../integration_test < commands.txt
echo

#test case 3
echo "lsa" >> commands.txt
truncate -s-1 commands.txt
echo "$ lsa"
echo
../integration_test < commands.txt
echo

#test case 4
echo "mkdir hello # ls" > commands.txt
truncate -s-1 commands.txt
echo "$ mkdir hello # ls"
echo
../integration_test < commands.txt
echo

#test case 5
echo "rmdir hello" > commands.txt
truncate -s-1 commands.txt
echo "$ rmdir hello"
echo
../integration_test < commands.txt
echo

#test case 6
echo "exit # not I exit" > commands.txt
truncate -s-1 commands.txt
echo "$ exit # now I exit"
echo
../integration_test < commands.txt
echo

rm commands.txt