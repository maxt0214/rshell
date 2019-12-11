echo "-Inpput Redirection Tests-"
echo

#test case 1
echo "ls > out.txt" > commands.txt
truncate -s-1 commands.txt
echo "$ ls > out.txt"
echo
../integration_test < commands.txt
echo

#test case 2
echo "sort < out.txt > out2.txt" > commands.txt
truncate -s-1 commands.txt
echo "$ sort < out.txt > out2.txt"
echo
echo "out2.txt: "
../integration_test < commands.txt
cat out2.txt
echo

#test case 3
echo "tr a-z A-Z < out.txt > out2.txt" > commands.txt
truncate -s-1 commands.txt
echo "$ tr a-z A-Z < out.txt >out2.txt"
echo
echo "out2.txt: "
../integration_test < commands.txt
cat out2.txt
echo

#test case 4
echo "(ls > out2.txt) || echo failed" > commands.txt
truncate -s-1 commands.txt
echo "$ (ls > out2.txt) || echo failed"
echo
echo "out2.txt: "
../integration_test < commands.txt
cat out2.txt
echo

#test case 5
echo "[out3.txt] ; pwd > out3.txt && test out3.txt" > commands.txt
truncate -s-1 commands.txt
echo "$ [out3.txt] ; pwd > out3.txt && test out3.txt"
echo
echo "out3.txt: "
../integration_test < commands.txt
cat out3.txt
echo

#test case 6
echo "tr a-z A-Z < out2.txt > out2.txt ; rm out.txt ; rm out2.txt ; rm out3.txt ; exit" > commands.txt
truncate -s-1 commands.txt
echo "$ tr a-z A-Z < out2.txt > out2.txt ; rm out.txt ; rm out2.txt ; rm out3.txt ; exit"
echo
../integration_test < commands.txt
echo

rm commands.txt