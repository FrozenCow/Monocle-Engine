#include "Tilemap.h"
#include "../Macros.h"
#include "../Graphics.h"
#include "../Debug.h"

namespace Monocle
{
	Tilemap::Tilemap(Tileset *tileset, int width, int height, int tileWidth, int tileHeight)
		: Graphic()
	{
		this->tileset = tileset;
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->Resize(width, height);
		this->Clear();


		/// TEST:
		for (int x = 0; x < width; x++)
			SetTile(x, 3, x);
	}

	void Tilemap::Resize(int width, int height)
	{
		std::vector<int> newTiles = std::vector<int>(width*height);

		int maxX = MIN(width, this->width);
		int maxY = MIN(height, this->height);
		for(int x=0;x<maxX;++x)
		{
			for(int y=0;y<maxY;++y)
			{
				newTiles[y*width+x] = tiles[y*this->width+x];
			}
		}

		this->width = width;
		this->height = height;

		tiles = newTiles;
	}

	// defaults to -1 (no tile)
	void Tilemap::Clear(int tileID)
	{
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				tiles[y * width + x] = tileID;
			}
		}
	}

	void Tilemap::GetWidthHeight(int *width, int *height)
	{
		*width = this->width;
		*height = this->height;
	}

	bool Tilemap::IsTile(int tx, int ty, int tileID)
	{
		return tiles[ty*width + tx] == tileID;
	}

	int Tilemap::GetTile(int tx, int ty)
	{
		return tiles[ty*width + tx];
	}

	void Tilemap::SetTile(int tx, int ty, int tileID)
	{
		tiles[ty*width + tx] = tileID;
	}

	int Tilemap::GetTileAtWorldPosition(const Vector2 &position)
	{
		int tx, ty;
		WorldToTile(position, &tx, &ty);
		return GetTile(tx, ty);
	}

	void Tilemap::SetTileAtWorldPosition(const Vector2 &position, int tileID)
	{
		int tx, ty;
		WorldToTile(position, &tx, &ty);
		return SetTile(tx, ty, tileID);
	}

	void Tilemap::WorldToTile(const Vector2 &position, int *tx, int *ty)
	{
		*tx = (int)(position.x / (float)tileWidth);
		*ty = (int)(position.y / (float)tileHeight);
	}

	void Tilemap::Update()
	{
	}

	void Tilemap::Render()
	{
		if (this->tileset)
		{
			//hack: make graphics::center?
			//Graphics::Translate(Vector2(400, 300));

			//Graphics::BindTexture(NULL);
			Graphics::BindTexture(tileset->texture);
			//Graphics::RenderQuad(400, 400);

			Vector2 texOffset;
			Vector2 texScale = Vector2(tileset->tileWidth / (float)tileset->texture->width, tileset->tileHeight / (float)tileset->texture->height);
			int tilesPerRow = tileset->texture->width / tileset->tileWidth;

			for (int tx = 0; tx < width; tx ++)
			{
				for (int ty = 0; ty < height; ty++)
				{
					int tileID = tiles[ty*width + tx];

					if (tileID != -1)
					{

						// get x/y coords of tile in tileset
						int tileX = (tileID % tilesPerRow) * tileset->tileWidth;
						int tileY = (tileID / tilesPerRow) * tileset->tileHeight;

						texOffset = Vector2(tileX/(float)tileset->texture->width, tileY/(tileX/(float)tileset->texture->width));
				
						// render quad with texture coords set
						Graphics::RenderQuad(tileWidth, tileHeight, texOffset, texScale, Vector2(tx * tileWidth + tileWidth*0.5f, ty * tileHeight + tileHeight*0.5f));
					}
				}
			}
		}
	}
}