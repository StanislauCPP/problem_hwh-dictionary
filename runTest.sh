for i in tests/*.test; do echo $i; ./tests/test.out < $i; done
