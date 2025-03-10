# How to add documentation ?

Create your README.md file(s) and add it to 'INPUT' in the doxyfile.in (line 968)

If you want to add link to a special section of your page, do it like that:

```markdown
## Table of Contents

1. <a href="#introduction">Introduction</a>
2. <a href="#configuration">Configuration</a>
3. <a href="#usage">Usage</a>
4. <a href="#links-to-detailed-pages">Links to Detailed Pages</a>
    - [Project Architecture](Architecture.md)
    - [Game Engine documentation](GameEngine/README.md)

...

## <a id="configuration"></a>Configuration
```

Don't forget to rebuild the doc with `./build.sh doc` !
