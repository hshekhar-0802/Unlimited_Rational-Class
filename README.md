# Unlimited_Rational-Class
A C++ class to handle mathematical computations without any integer overflow.
<h2>UnlimitedInt</h2> 
This is a custom integer data type designed to handle integers of arbitrary size without any limitations on their magnitude.  Unlike standard integer types in programming languages, such as int or long, which have fixed ranges, UnlimitedInt can represent extremely large or precise integer values. This class is a fundamental building block for working with integers in situations where traditional integer types fall short due to their size limitations.
<h3>Class Description</h3>
The UnlimitedInt class has the following attributes and methods:
<ul>
  <li><strong><em>size:</em></strong> An integer that represents the size of the UnlimitedInt object.</li>
  <li><strong><em>capacity:</em></strong> An integer that represents the capacity of the UnlimitedInt object.</li>
  <li><strong><em>sign:</em></strong> An integer that indicates the sign of the UnlimitedInt object. It is set to 1 for positive numbers and -1 for negative numbers. </li>
  <li><strong><em>unlimited_int:</em></strong> An integer pointer that points to an array storing the unlimited integer.</li>
  <li><strong><em>get_capacity:</em></strong>  Returns the capacity of the UnlimitedInt object.</li>
  <li><strong><em>get_size:</em></strong> Returns the size of the UnlimitedInt object.</li>
  <li><strong><em>get_array:</em></strong> Returns a pointer to the array storing the UnlimitedInt digits.</li>
  <li><strong><em>get_sign:</em></strong> Returns the sign of the UnlimitedInt object (1 for positive, -1 for negative).</li>
  <li><strong><em>to_string:</em></strong> Convert a UnlimitedInt object to its string representation. For eg. "5" for 5 and "-5" for -5</li>
  <li><strong><em>Arithmetic operations such as addition, subtraction, multiplication, division, modulus for UnlimitedInt objects.</em></strong></li>
</ul>
<h2>Rationals with UnlimitedInt</h2>
A rational number is typically represented in the form p/q, where p and q are integers (Z), p and q are coprime (meaning they have no common divisors other than 1), and q ̸= 0.<br>
The UnlimitedRational class extends the concept of rational numbers by using the UnlimitedInt class for its numerator and denominator. This allows you to accommodate even the most extensive calculations in scenarios where standard floating-point representations might suffer from precision loss.
<h3>UnlimitedRational Class</h3>
The UnlimitedRational class includes the following attributes and methods:
<ul>
  <li><strong><em>p and q:</em></strong> Pointers to UnlimitedInt objects representing the numerator and denominator, respectively. (Remember, p and q must be coprime, or your implementation will not pass our tests.) Note if p is 0, any non-zero value of q will be acceptable for the denominator.</li>
  <li><strong><em>get_p() and get_q():</em></strong> Methods to access the numerator and denominator as UnlimitedInt objects.</li>
  <li><strong><em>get_p_str() and get_q_str():</em></strong>  Methods to retrieve the numerator and denominator as string representations.</li>
  <li><strong><em>get_frac_str():</em></strong> Method to return the rational number as a string in the form ”p/q”. If p/q is positive, then both ”p/q” and ”-p/-q” would be acceptable as answers. Similarly if p/q is negative, then the ”-”sign can be either in the numerator or the denominator.</li>
  <li><strong><em>Arithmetic operations such as addition, subtraction, multiplication, division for UnlimitedRational objects.</em></strong></li>
</ul>
<h3>Error Conditions</h3>
<ul>
  <li>In case of division by 0, the answer will be 0/0.</li>
  <li>Any operation with 0/0 as one of the operands must return 0/0 as the correct answer.</li>
</ul>
<h2>Using the class</h2>
To use the classes, place all the 4 files (ulimitedint.cpp, ulimitedint.h, ulimitedrational.cpp, ulimitedrational.h) in a single directory and then you have to construct a main.cpp file, initializing UnlimitedInt object and/or UnlimitedRational objects and then perform calculations using the functions discussed above.<br>
The main.cpp files here includes the code to print 20000 factorial for ulimitedint class and that of ulimitedrational class contains code for simple division of two fractions -1/3 and 1/2.<br>
To compile the files, simply run the following commands:
<ul>
  <li><strong>UlimitedInt Class: </strong> <em>"g++ main.cpp ulimitedint.cpp -o test"</em> and then <em>"./test"</em> </li>
  <li><strong>UlimitedRational Class: </strong> <em>"g++ main.cpp ulimitedint.cpp ulimitedrational.cpp -o test"</em> and then <em>"./test"</em> </li>
  <li><strong><em>Make sure to add the following line in the main.cpp file: <br>#include "ulimitedrational.h" </strong></li>
</ul>
