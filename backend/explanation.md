https://gemini.google.com/share/144c24af3d84



an **unsigned integer** is used as it only contains zero and **+ve numbers**



the major error i ran into:

It’s a very subtle C++ syntax error in your while loop that is likely causing your hash to be calculated incorrectly every single time.

The Bug: Operator Precedence
Look at this line in your load\_to\_md:

C++
while (inByte = BIO\_read(bio\_in, inBuffer, sizeof(inBuffer)) > 0)
In C++, the "greater than" (>) operator has higher priority than the "assignment" (=) operator.

What you want: Assign the result of BIO\_read to inByte, then check if it's > 0.

What is happening: The compiler evaluates BIO\_read(...) > 0 first. This returns a boolean (1 for true, 0 for false). Then, it assigns that 1 or 0 to inByte.

Because inByte becomes 1, your EVP\_DigestUpdate is only processing 1 byte of your buffer at a time, and it's likely processing the wrong data. Since the loop only sees "1" or "0", it doesn't matter what you write to the file; the hash isn't actually reflecting the full content.

The Fix: Add Parentheses
You must wrap the assignment in parentheses so the value is assigned before the comparison:

C++
// Corrected Loop
while ((inByte = BIO\_read(bio\_in, inBuffer, sizeof(inBuffer))) > 0) {
EVP\_DigestUpdate(mdctx, inBuffer, inByte);
}
Why this explains the Tamper Test failure
When inByte is always 1, you are effectively hashing only the very first byte of each 4096-byte chunk, or worse, you're hashing a sequence of 0x01 values.

If your two test strings both start with the same character (like 'T' in "Transfer"), and the rest of the hashing is broken due to this logic error, the resulting "broken" hash might accidentally look the same to the verify function, or the md\_value is simply not being populated with enough unique data to fail.



**don't limit ur self to using ai. ask an agent about a topic, basics and then search in depth about that on the internet.**

a **unique pointer** is a special type of pointer where only one pointer can store the address of the file.
in normal pointers, if more than one pointer points to the same file, issues can arise.



Basically, file cryption works on a principle of cryptography. i have added some process management to it.

