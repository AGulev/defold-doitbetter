# Android

Defold doesn't support using `aar` in lib folder (using Gradle config it works fine, but then libs should be available on maven repo). So, before using `aar` unpack them. Put `jar` files into `doitbetter/lib/android` folder and `AndroidManifest.xml` from `doitbetter.aar` into `doitbetter/manifests/android` folder.
