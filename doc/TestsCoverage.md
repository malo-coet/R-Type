# How to see the coverage of the unit tests ?

/!\ Install gcovr before /!\

## See the coverage

```bash
gcovr --root . --filter RType/ --exclude tests/ --exclude build/ --exclude ".*Main\.cpp" --txt-metric branch
```

## Exporting the coverage data

```bash
gcovr --root . --filter RType/ --exclude tests/ --exclude build/ --exclude ".*Main\.cpp" --html --html-details -o coverage/coverage.html
```

[Here!](coverage/coverage.html)
