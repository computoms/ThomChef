TODO
====

# Refactoring

* Change enumerations (category, unit types) to static classes with friendly names, etc so that it's easier to convert to string and display
* Add ingredient category: some ingredients are always available (sugar, flour, pasta?, salt, pepper etc.) and some not (potatoes, cheese, meat etc.)
	- Recipes containing all ingredients listed + always available ingredients => potential candidates. In this case, the filter should be set to "recipes containing part of these ingredientst"
	- This means the filter should contain default ingredients (such as salt&pepper, etc)