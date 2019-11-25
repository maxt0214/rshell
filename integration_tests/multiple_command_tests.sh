echo "-Multiple Command Tests-"
echo

#test case 1
echo "lsa || pwd" > commands.txt
truncate -s-1 commands.txt
echo "$ lsa || pwd"
echo
../integration_test < commands.txt
echo

#test case 2
echo "pwd && ls ; echo hello || lsa && touch main.cpp ; echo file created" > commands.txt
truncate -s-1 commands.txt
echo "$ pwd && ls ; echo hello || lsa && touch main.cpp ; echo file created"
echo
../integration_test < commands.txt
echo

#test case 3
echo "rm main.cpp ; echo file removed" > commands.txt
truncate -s-1 commands.txt
echo "$ rm main.cpp ; echo file removed"
echo
../integration_test < commands.txt
echo

#test case 4
echo "pwd || rm && echo hi #this is a comment" > commands.txt
truncate -s-1 commands.txt
echo "$ pwd || rm && echo hi #this is a comment"
echo
../integration_test < commands.txt
echo

#test case 6
echo "exit # not I exit" > commands.txt
truncate -s-1 commands.txt
echo "$ exit # not I exit"
echo
../integration_test < commands.txt
echo

rm commands.txt