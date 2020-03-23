 - doublons : marchent pas
 - dans configuration : nombre repas long / rapide par défaut (5/4)


 ## Refactoring


* Change enumerations (category, unit types) to static classes with friendly names, etc so that it's easier to convert to string and display
* Implement an iterator for the ingredients
* Implement an iterator for the recipes inside RecipeStore
* Create the XML file if it does not exist yet (for first startup)