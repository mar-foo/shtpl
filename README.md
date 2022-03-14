# Shell template
A simple program to preprocess templates.

## Template syntax

Every text block enclosed in ```{{}}``` is considered a template, text
is interpreted as a shell command and the block is substituted with the
output of the command.

### Example
```
$ echo "shtpl is a simple program: it's only {{wc -l template.c | cut -d\  -f1}} lines long!" | shtpl
shtpl is a simple program: it's only 78
 lines long!
```

## Bugs
* Does not trim last newline in the output
* Probably sucks
