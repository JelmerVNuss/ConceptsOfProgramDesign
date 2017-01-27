
# Tuple CSV Parser
This project shows the purpose of using C++ Template Metaprogramming to let the compiler construct parsing intstructions for each column in a csv.
The types which corresond to a field in the CSV should be known before reading the CSV.
This is done by defining a tuple with corresponding types.
This means that with a CSV like:

```
1;Michiel;5
2;Thomas;10
3;Hugo;20
4;Robin;40
5;Jelmer;80
```

Corresponds to a tuple like:

```
tuple<int, std::string, int>
```

Using the CsvIterator in combination with the CsvHelper it is possible to let the compiler generate parsing instructions
for each of the elements within the tuple.

The CsvHelper class is where the Template Metaprogramming is really happening. It will iterate through the
tuple using tail-recursion and will then try to parse a field within a given row of the csv to the corresponding type.

This will look something like this:

```
tuples::get<0>(tuple) = (castToTypeHere)*i;
++i;
tuples::get<1>(tuple) = (castToTypeHere)*i;
++i;
```
Where the 0 and 1 are the indices of the corresponding element in the tuple and i is the string-value of the field at that index.