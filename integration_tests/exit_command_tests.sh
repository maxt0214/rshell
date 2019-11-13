#test case 1
echo "# exit" > commands.txt

#test case 2
echo "exit" >> commands.txt
truncate -s-1 commands.txt

echo "-Exit Command Tests-" >> result.txt
../rshell < commands.txt >> result.txt