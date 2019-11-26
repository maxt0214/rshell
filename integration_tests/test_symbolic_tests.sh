echo "-Test Symbolic Command Tests-"
echo

#test case 1
echo "[-e ../prototype]" > commands.txt
truncate -s-1 commands.txt
echo "$ [-e ../prototype]"
echo
../integration_test < commands.txt
echo

#test case 2
echo "[-f ../prototype]" > commands.txt
truncate -s-1 commands.txt
echo "$ [-f ../prototype]"
echo
../integration_test < commands.txt
echo

#test case 3
echo "[-d ../prototype]" > commands.txt
truncate -s-1 commands.txt
echo "$ [-d ../prototype]"
echo
../integration_test < commands.txt
echo

#test case 4
echo "[-f ../README.md]" > commands.txt
truncate -s-1 commands.txt
echo "$ [-f ../README.md]"
echo
../integration_test < commands.txt
echo

#test case 5
echo "[-f ../names.txt]" > commands.txt
truncate -s-1 commands.txt
echo "$ [-f ../names.txt]"
echo
../integration_test < commands.txt
echo

#test case 6
echo "[../prototype]" > commands.txt
truncate -s-1 commands.txt
echo "$ [../prototype]"
echo
../integration_test < commands.txt
echo

#test case 7
echo "[../prototype] && ls && (pwd ; echo hi)" > commands.txt
truncate -s-1 commands.txt
echo "$ [../prototype] && ls && (pwd ; echo hi)"
echo
../integration_test < commands.txt
echo

#test case 8
echo "([../prototype] && ls) && (pwd ; echo hi)" > commands.txt
truncate -s-1 commands.txt
echo "$ ([../prototype] && ls) && (pwd ; echo hi)"
echo
../integration_test < commands.txt
echo

#test case 9
echo "([../prototype && ls && (pwd ; echo hi)" > commands.txt
truncate -s-1 commands.txt
echo "$ ([../prototype && ls && (pwd ; echo hi)"
echo
../integration_test < commands.txt
echo

rm commands.txt