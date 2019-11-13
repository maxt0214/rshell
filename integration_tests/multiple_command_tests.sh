#test case 1
echo "lsa || pwd" > commands.txt

#test case 2
echo "pwd && ls ; echo hello || lsa && touch main.cpp ; echo file created" >> commands.txt

#test case 3
echo "rm main.cpp ; echo file removed" >> commands.txt

#test case 4
echo "pwd || rm && echo hi #this is a comment" >> commands.txt

#test case 6
echo "exit # not I exit" >> commands.txt
truncate -s-1 commands.txt

echo "-Multiple Command Tests-" >> result.txt
../rshell < commands.txt >> result.txt