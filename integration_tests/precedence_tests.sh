echo "-Precedence Tests-"
echo

#test case 1
echo "(ls && pwd) || (echo hi && echo bye)" > commands.txt
truncate -s-1 commands.txt
echo "$ (ls && pwd) || (echo hi && echo bye)"
echo
../integration_test < commands.txt
echo

#test case 2
echo "((ls && pwd) || (echo hi && echo bye))" > commands.txt
truncate -s-1 commands.txt
echo "$ ((ls && pwd) || (echo hi && echo bye))"
echo
../integration_test < commands.txt
echo

#test case 3
echo "((ls && pwd) || (echo hi && echo bye)) ; (hi || echo Oops)" > commands.txt
truncate -s-1 commands.txt
echo "$ ((ls && pwd) || (echo hi && echo bye)) ; (hi || echo Oops)"
echo
../integration_test < commands.txt
echo

#test case 4
echo "(ls && pwd) || (echo hi && echo bye" > commands.txt
truncate -s-1 commands.txt
echo "$ (ls && pwd) || (echo hi && echo bye"
echo
../integration_test < commands.txt
echo

#test case 5
echo "((ls && pwd) || (echo hi && echo bye)" > commands.txt
truncate -s-1 commands.txt
echo "$ ((ls && pwd) || (echo hi && echo bye)"
echo
../integration_test < commands.txt
echo

#test case 6
echo "(((ls && pwd) || (echo hi && echo bye))" > commands.txt
truncate -s-1 commands.txt
echo "$ (((ls && pwd) || (echo hi && echo bye))"
echo
../integration_test < commands.txt
echo

#test case 6
echo "(((ls && pwd) || (echo hi && echo bye)))" > commands.txt
truncate -s-1 commands.txt
echo "$ (((ls && pwd) || (echo hi && echo bye)))"
echo
../integration_test < commands.txt
echo

rm commands.txt