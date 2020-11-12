# Notes for Golang General

## Basics
Go code <- packages <- Go files __in a directory__

`package main` is for executable program only and `func main() {}` is the entry point of the program.

Newlines with certain tokens is similar with semicolons in C. Therefore, where to break lines is significant.

### Command Arguments
`os.Args` -> a slice of strings. `os.Args[0]` is the program name.

### Variable and Const
```
s := ""
var s string
var s = ""
var s string = ""
var i, j, k int                 // int, int, int
var b, f, s = true, 2.3, "four" // bool, float64, string
var f, err = os.Open(name) // os.Open returns a file and an error
i, j = j, i // swap values of i and j
```
If not value is provided to initialize the varialbe, __zero value__ is used. 

Notice that `:=` is different from `=` assignment.

"One subtle but important point: a short variable declaration does not necessarily
declare all the variables on its left-hand side. If some of them were already 
declared in the __same lexical block (§2.7)__, then the short variable declaration 
acts like an assignment to those variables."
-- The Go Programming Language
```
const (
    C1 = 0
    C2 = 1
)
const C1 = 0
```

### Zero Value
numbers: 0
boolean: false
string: ""
interface: nil
reference types (slice, pointer, map, channel, function): nil

"in Go there is no such thing as an uninitialized variable."
-- The Go Programming Language.
### struct

A `struct` can be initialized with _composite literals_, like `gif.GIF{...}`. 
Fields that are not set have __zero value__.
### If & Switch
```
if i > 0 {

} else if i = 0 {

} else {

}
```
```
switch s {
case "a":
    // no fallthrough
    a++
case "b":
    b++
default:
    c++
}
switch {
case i > 0:
    a++
default:
    b++
}
```


### Loop
```
for i := 0; i < 10; i++ {

}
```
```
for i < 10 {

}
```
```
for {
    // infinite
}
```
```
for idx, val := range os.Args[1:] {
    // range usage
}
```

### Naming & Visibility
Naming is related to visibility at package level in Go. A name begins with a 
upper-case letter will be exported by its package.

Naming style lean towards simple names for local variables, camel case for 
composite names and acronyms are rendered in the same case (such as "html" or 
"HTML").

### Pointer
It is okay to return the address of an local variable in a function. Each call 
to the function yields a different address (different variable therefore).

`new` can create a pointer to a unamed variable of a specific type, such as
`p := new(int)`. The initial value is __zero value__. Not used often though,
as the following is used:
```
p := &Point{1, 2}
// equals to
p := new(Point)
*p = Point{1, 2}
```

## Command Data Structures
### Map
A map, like `map[string]string` is passed by reference. (Not a consistent
desgin. Especially when you only look at paramemters of functions which 
consist of pointers, maps etc). Or not really, if regarding a map as a struct 
with internal pointers, then we pass value for the struct, but reference for 
the map.
