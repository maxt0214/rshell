echo "-Inpput Redirection Tests-"
echo

ls > out.txt

#test case 1
echo "cat < out.txt" > commands.txt
truncate -s-1 commands.txt
echo "$ cat < out.txt"
echo
../integration_test < commands.txt
echo

#test case 2
echo "sort < out.txt" > commands.txt
truncate -s-1 commands.txt
echo "$ sort < out.txt"
echo
../integration_test < commands.txt
echo

#test case 3
echo "tr a-z A-Z < out.txt" > commands.txt
truncate -s-1 commands.txt
echo "$ tr a-z A-Z < out.txt"
echo
../integration_test < commands.txt
echo

#test case 4
echo "cat < out.txt && echo \"Print CMakeLists out\"" > commands.txt
truncate -s-1 commands.txt
echo "$ cat < out.txt && echo \"Print CMakeLists out\""
echo
../integration_test < commands.txt
echo

#test case 5
echo "(cat < out.txt) || echo this will not print out" > commands.txt
truncate -s-1 commands.txt
echo "$ (cat < out.txt) || echo this will not print out"
echo
../integration_test < commands.txt
echo

#test case 6
echo "cat < out.txt ; exit" > commands.txt
truncate -s-1 commands.txt
echo "$ cat < out.txt ; exit"
echo
../integration_test < commands.txt
echo

rm commands.txt
rm out.txt