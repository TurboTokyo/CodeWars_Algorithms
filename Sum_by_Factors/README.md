# Prime Factor Sums

This is a simple C program that calculates the sum of numbers in a list that are divisible by each prime number up to the maximum absolute value in the list.

## How it Works

The program accepts a list of integers as command line arguments. It then checks each prime number up to the maximum absolute value in the list, and if a list member is divisible by the prime number, it adds that number to the sum for that prime. The program finally prints a string that shows each prime along with its corresponding sum.

## Compilation

You can compile this program using gcc:

```
gcc -o prime_factor_sums main.c
```

## Usage

After compiling, you can run the program like this:

```
./prime_factor_sums 12 15
```

This will output:

```
(2 12)(3 27)(5 15)
```

## License

This project is licensed under the GNU General Public License (GPL).
