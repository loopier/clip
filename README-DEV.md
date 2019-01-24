# README for DEVELOPERS

## Build an OSX application bundle
See https://stackoverflow.com/a/30792824

1. Make the following directory structure

  - `clip.app/`
    - `Contents/`
      - `MacOS/`
      - `Resources/`

1. Copy OpenFramworks' project `bin/` contents to `clip.app/Contents/Resources/`.  
1. Rename `whateverTheClipServerAppIsCalled.app` as `clipserver.app`.  **WARNING!!!:** **You should also rename the executable inside `clipserver.app/Contents/MacOS/` to `serverapp`**.
1. Place ***[### !!!] THIS SCRIPT [!!! ###]*** inside MacOS and name it **EXACLTY** as the bundle without extension
1. So the finial structure should be like this

  ```
  clip.app/
    Contents/
      MacOS/
        clip
      Resources/
        clipserver.app/
          Contents/
            ...
            MacOS/
              clipserver
            ...          
        cliplang/
          ... (python scripts for cliplang)
        data/
          ... (contents of OpenFramworks bin/data/ folder)
  ```
