
# Runtime Metaprogramming
While this does kind of defeat the purpose of our template metaprogramming research, we've also included a "run-time" metaprogramming approach.

What this project does is:

You can, using some kind of define flag, force your program to use the CsvParser class.
This is a class which opens a CSV file, and parses it to a struct containing:
The first row of the CSV, so the field names, as properties.
The second row of the CSV, the types it should expect, as template parameters.

This means that 

```
id;name;additional
int;string;int
1;Michiel;5
2;Thomas;10
3;Hugo;20
4;Robin;40
5;Jelmer;80
```

Can get parsed to a struct like:

```cpp
struct TestCsv {
	static CsvCollumn<int> id() { return CsvCollumn<int>("id", 0, ';');}
	static CsvCollumn<string> name() { return CsvCollumn<string>("name", 1, ';');}
	static CsvCollumn<int> additional() { return CsvCollumn<int>("additional", 2, ';');}
};
```

This is generated using strings and file input and output during runtime.
But while this is not template metaprogramming, it does provide the user with actual type information and compile-time typechecking.

The program will do this parsing when calling the CsvParser to parse with a filename.

```cpp
#ifdef _PARSE
    CsvParser parser;
    parser.ParseToTemplate("TestCsv.csv", ';');
    exit(0);
#else
```

The CsvParser class also contains some old code that might be interesting that generates template-metaprogramming-friendly lists of characters.