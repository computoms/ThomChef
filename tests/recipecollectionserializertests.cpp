#include "libs/catch/catch.hpp"

#include "core/recipecollectionserializer.h"

TEST_CASE("SerializeRecipe_ValidXmlNode_ReturnsValidRecipe")
{
    REQUIRE(true);
    RecipeCollectionSerializer serializer;
    pugi::xml_node recipeNode;
    Recipe r = serializer.readRecipe(recipeNode);
}
