echo "-Commented Command Tests-"
echo

#test case 1
echo "ls # lsa || pwd" > commands.txt
truncate -s-1 commands.txt
echo "$ ls # lsa || pwd"
echo
../integration_test < commands.txt
echo

#test case 2
echo "pwd # lsa || pwd" > commands.txt
truncate -s-1 commands.txt
echo "$ pwd # lsa || pwd"
echo
../integration_test < commands.txt
echo

#test case 3
echo "lsa # lsa ; pwd" > commands.txt
truncate -s-1 commands.txt
echo "$ lsa # lsa ; pwd"
echo
../integration_test < commands.txt
echo

#test case 4
echo "# ls && pwd" > commands.txt
truncate -s-1 commands.txt
echo "$ # ls && pwd"
echo
../integration_test < commands.txt
echo

#test case 5
echo "echo this should be printed out # echo this should not be printed out" > commands.txt
truncate -s-1 commands.txt
echo "$ echo this should be printed out # echo this should not be printed out"
echo
../integration_test < commands.txt
echo

#test case 6
echo "exit # now I exit" > commands.txt
truncate -s-1 commands.txt
echo "$ exit # now I exit"
echo
../integration_test < commands.txt
echo

rm commands.txt