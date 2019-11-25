echo "-Exit Command Tests-"
echo

#test case 1
echo "# exit" > commands.txt
truncate -s-1 commands.txt
echo "# exit"
echo
../integration_test < commands.txt
echo

#test case 2
echo "exit" > commands.txt
truncate -s-1 commands.txt
echo "exit"
echo
../integration_test < commands.txt
echo

rm commands.txt