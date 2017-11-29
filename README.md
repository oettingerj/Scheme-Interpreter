`kleene-project`
================

#### Collaborators: Josh Oettinger, Nathaniel Lovin, Tenzin Dolphen

This is a `Scheme` interpreter written in `C` as a final project for CS251.

---

## TODO
-   [x] Previously, if a `CONS_TYPE` wasn't any of the special forms, our eval method just printed out its value. We should fix this, because it prevents the program from catching a lot of bad syntax.
    -   I fixed this by evaluating the value of bindings at the time of binding (except letrec) so that lists can be returned without having to be evaluated. This way, any `CONS_TYPE` that doesn't fall into any of our if statements in `eval` can be recognized as bad syntax or another error.
-   [x] For some reason, `(+)` does not seem to call the plus function correctly, but `(+ )` does.
    -   This was an issue with our tokenizer only marking `+` as a symbol if there was a space after it.
-   [ ] Add quote shorthand (`'`)
