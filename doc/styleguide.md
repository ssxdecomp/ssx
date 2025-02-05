# Style guide

This is pretty simple.

## General formatting

The SSX codebase and second-party components used Allman brace style, so we're going to stick with that.

```cpp
if(i == 2)
{
    // Do something
}
```

## Naming

The SSX codebase tends to be a bit all over the place naming wise.

## For second-party components (REAL, SND, SPCH)

<!-- TODO: Finish this. REAL/SND code style is largely very different, since it was written by multiple differing teams and at ~2000 was about 5-6 years old. -->

Second party components largely written in C (or being started to be refactored in C++) name their functions like `[component in uppercase]_[name in lowercase]`.

e.g: `SND_initsys` etc etc.

SPCH is primairly C++ but also uses this C interface pattern.

## For SSX code

Variables use a subset of Systems Hungarian, with some changes. (Function parameters seem to randomly choose to use Hungarian notation or not, so you can worry about using it less there.)

The advised subset is something like this:

| Prefix | Meaning            | Example            |
| ------ | ------------------ | ------------------ |
| `p`    | pointer            | `void* pThing;`    |
| `i`    | integer            | `int iCount;`      |
| `s`    | short              | `tInt16 sUnk;`     |
| `u`    | unsigned (integer) | `tUint32 uiThing;` |
| `sz`   | ASCII string       | `char* pszItem;`   |

Types are marked in camel case:

| Prefix | Meaning          | Example          |
| ------ | ---------------- | ---------------- |
| `e`    | `enum`           | `eValue`         |
| `t`    | `typedef struct` | `tDrawInfo`      |
| `c`    | `class`          | `cBezierManager` |

There are also special prefixes for variables used in certain cases:

| Prefix | Meaning                                      | Example             |
| ------ | -------------------------------------------- | ------------------- |
| `m`    | class member                                 | `void* mpData`      |
| `g`    | global                                       | `int gCounter`      |
| `The`  | global also (seems to mostly be for classes) | `cThing* TheThing;` |

Function names are Pascal case regardless of scope (either namespace or class member).

Note that Asyncsys uses second party function naming for.. some reason.

## Examples

A good example of code which follows the style:

```cpp
class cManager
{
public:
    BX_REAL_ALLOCATED("Manager");

    cManager(int param)
    {

    }

    // does something.
    void DoThing();
};

void cManager::DoThing()
{
    return;
}
```

A bad example, which will need to be altered.

```cpp
class CManager {
    public:

    CManager(int Param) {}

    void do_Thing() {

    }
};
```
