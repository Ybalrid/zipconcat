# zipconcat
CLI Tool to append a zip archive to an executable (or anything really...)

## Usage

  $ zipconcat /path/to/exeutable/ /path/to/zip/archive.zip
  
This will output a file with the same name of the executable, but with 
".output" inserted before it's extension (if it had one. If no extensions, it 
will append a .exe file)

The resulting file can be oppened "as if" it was the zip archive, and can run 
"as if" it was the original executable.

## Example Usecase

 - Video Game main executable with an engine that can pull resources from a 
.zip file. This avoid clutter, and give you a good place where to stash 
read-only resources
  
