## Requirements

Requires [gcc](https://gcc.gnu.org/install/). You can also install [make](https://www.gnu.org/software/make/) to use Makefile.

## Comands

### `make build`

Compiles an application to `application`.

Or you can use `gcc`:

```sh
gcc main.c -o application
```

### `make starts`

Compiles an application to `application` and runs it.

```sh
make build && ./application
```
