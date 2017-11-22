#include "../include/TMXParser.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
namespace TMX {

  Parser::Parser( const char* filename )
  {
    load( filename );
  }

  Parser::Parser()
  {
  }

  Parser::~Parser()
  {
  }

  bool Parser::load( const char* filename )
  {
    std::string version = VERSION;
    rapidxml::xml_node<>* root_node;
    rapidxml::xml_document<> doc;
    rapidxml::file<> file( filename );
    doc.parse<0>( file.data() );
    //get root nodes
    root_node = doc.first_node( "map" );

    //load map element
    if( root_node->first_attribute( "version" )->value() != version ) {
      std::cout << "ERROR: Map version mismatch. Required version: " << VERSION << "." << std::endl;
      return false;
    }

	mapInfo.version = root_node->first_attribute( "version" )->value();
    mapInfo.orientation = root_node->first_attribute( "orientation" )->value();
    mapInfo.width = std::atoi( root_node->first_attribute( "width" )->value() );
    mapInfo.height = std::atoi( root_node->first_attribute( "height" )->value() );
    mapInfo.tileWidth = std::atoi( root_node->first_attribute( "tilewidth" )->value() );
    mapInfo.tileHeight = std::atoi( root_node->first_attribute( "tileheight" )->value() );

    if( root_node->first_attribute( "backgroundcolor" )->value() != 0 ) {
      mapInfo.backgroundColor = root_node->first_attribute( "backgroundcolor" )->value();
    }

    if( root_node->first_node( "properties" ) != 0 ) {
      for( rapidxml::xml_node<>* properties_node = root_node->first_node( "properties" )->first_node( "property" ); properties_node; properties_node = properties_node->next_sibling() ) {
        mapInfo.property[properties_node->first_attribute( "name" )->value()] = properties_node->first_attribute( "value" )->value();
      }
    }

    std::cout << std::endl;

    for( rapidxml::xml_node<>* tileset_node = root_node->first_node( "tileset" ); tileset_node; tileset_node = tileset_node->next_sibling( "tileset" ) ) {
      Tileset tmpTileset;
      tmpTileset.firstGID = std::atoi( tileset_node->first_attribute( "firstgid" )->value() );
      tmpTileset.source = tileset_node->first_attribute( "source" )->value();
      tilesetList.push_back( tmpTileset );
    }

    for( rapidxml::xml_node<>* layer_node = root_node->first_node( "layer" ); layer_node; layer_node = layer_node->next_sibling( "layer" ) ) {
      TileLayer layer;
      layer.name = layer_node->first_attribute( "name" )->value();

	  layer.opacity = 1;

      if( layer_node->first_node( "properties" ) != 0 ) {
        for( rapidxml::xml_node<>* properties_node = layer_node->first_node( "properties" )->first_node( "property" ); properties_node; properties_node = properties_node->next_sibling() ) {
          layer.property[properties_node->first_attribute( "name" )->value()] = properties_node->first_attribute( "value" )->value();
        }
      }

      rapidxml::xml_node<>* data_node = layer_node->first_node( "data" );
      layer.data.encoding = data_node->first_attribute( "encoding" )->value();

      if( data_node->first_attribute( "compression" ) > (void *)0 ) {
        layer.data.compression = data_node->first_attribute( "compression" )->value();
      }

      layer.data.contents = data_node->value();
      tileLayer[layer.name] = layer;
    }

    for( rapidxml::xml_node<>* oGroup_node = root_node->first_node( "objectgroup" ); oGroup_node; oGroup_node = oGroup_node->next_sibling( "objectgroup" ) ) {
      ObjectGroup oGroup;
      oGroup.color = oGroup_node->first_attribute( "color" )->value();
      oGroup.name = oGroup_node->first_attribute( "name" )->value();
      oGroup.opacity = std::atof( oGroup_node->first_attribute( "opacity" )->value() );
      oGroup.visible = std::atoi( oGroup_node->first_attribute( "visible" )->value() );

      if( oGroup_node->first_node( "properties" ) != 0 ) {
        for( rapidxml::xml_node<>* properties_node = oGroup_node->first_node( "properties" )->first_node( "property" ); properties_node; properties_node = properties_node->next_sibling() ) {
          oGroup.property[properties_node->first_attribute( "name" )->value()] = properties_node->first_attribute( "value" )->value();
        }
      }

      objectGroup[oGroup.name] = oGroup;
    }

    for( rapidxml::xml_node<>* image_node = root_node->first_node( "imagelayer" ); image_node; image_node = image_node->next_sibling( "imagelayer" ) ) {
      ImageLayer imgLayer;
      imgLayer.name = image_node->first_attribute( "name" )->value();

      if( image_node->first_attribute( "opacity" ) != 0 ) {
        imgLayer.opacity = std::atof( image_node->first_attribute( "opacity" )->value() );
      }

      imgLayer.visible = std::atoi( image_node->first_attribute( "visible" )->value() );

      imgLayer.image.source = image_node->first_node( "image" )->first_attribute( "source" )->value();

      if( image_node->first_node( "image" )->first_attribute( "trans" ) != 0 ) {
        imgLayer.image.transparencyColor = image_node->first_node( "image" )->first_attribute( "trans" )->value();
      }

      if( image_node->first_node( "properties" ) != 0 ) {
        for( rapidxml::xml_node<>* properties_node = image_node->first_node( "properties" )->first_node( "property" ); properties_node; properties_node = properties_node->next_sibling( "property" ) ) {
          imgLayer.property[properties_node->first_attribute( "name" )->value()] = properties_node->first_attribute( "value" )->value();
        }
      }

      imageLayer[imgLayer.name] = imgLayer;
    }

    return true;
  }
}
