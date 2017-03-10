# path

`path` finds a valid file in the $PATH variable; it more or less implements the functionality of `which`.

## Synopsis

    path [options] [--] command

## Options

- `-a`: show all possible results (instead of just he first result, which is the default behaviour)
- `-d /path/to/directory[:/path/to/drectory2[:/path/to/drictory3 ...]]`: include the specified directory/directories in the search
- `-q`: quiet mode (do not print 'not found' line if the command cannot be found).
- `-h`: show help
- `-v`: verbose mode (list every directory that is searched and show if a search fails)
