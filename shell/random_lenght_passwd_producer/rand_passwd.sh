#!/bin/bash
random_len=16
random=$(cat /dev/urandom |tr -cd [:alnum:] |fold -w${random_len} |head -n 1)
echo $random
