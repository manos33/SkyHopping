#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include "util.h" 




void Level::drawEnemy(int i) {

	Box& enemy = m_enemies[i];

	
	float x = enemy.m_pos_x + m_state->m_global_offset_x;
	float y = enemy.m_pos_y + m_state->m_global_offset_y;


	m_enemy_brush.texture = m_state->getFullAssetPath("creature1-1.png");
	graphics::drawRect(x, y, m_enemy_size, m_enemy_size, m_enemy_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);
}

void Level::moveEnemy(int i) {
	Box& enemy = m_enemies[i];
	enemy.m_pos_x += 0.5f * 0.06f;
	if (enemy.m_pos_x > 16.0f)
		enemy.m_pos_x = -8.0f;


}



void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	std::string& name = m_block_names[i % m_block_names.size()];

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;

	m_block_brush.texture = m_state->getFullAssetPath(name);

	graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);

}

void Level::checkCollisions()
{
	

		if (m_state->getPlayer()->intersect(trophy)) {
			levelPassed = true;
		}
		
	

	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(block))
		{
			m_state->getPlayer()->m_pos_y += offset;
			m_state->getPlayer()->m_vy = 0.0f;


			break;
		}
	}

	checkSidewaysColl(m_blocks);
	checkSidewaysColl(m_enemies);

	


}

void Level::checkSidewaysColl(std::vector<Box> m_vector) {
	for (auto& thing : m_vector)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(thing))
		{
			m_state->getPlayer()->m_pos_x += offset;

			m_state->getPlayer()->m_vx = 0.0f;
			break;
		}

	}



}

void Level::update(float dt)
{

	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);

	m_time += dt;
	float displacement = 0.02f * sin(0.007f * m_time);
	trophy.m_pos_y += displacement;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		moveEnemy(i);
	}
	checkCollisions();
	if (levelPassed == true) {
		graphics::drawText(1.0f, 3.0f, 1.0f, "YOU WIN", m_text_brush);
	}

	GameObject::update(dt);
}

void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x = m_state->m_global_offset_x / 15.0f + w / 2.0f;
	float offset_y = m_state->m_global_offset_y / 15.0f + h / 2.0f;

	//draw background
	graphics::drawRect(offset_x, offset_y, 4.0f * w, 2.0f * h, m_brush_background);


	//draw trophy
	float x = trophy.m_pos_x + m_state->m_global_offset_x;
	float y = trophy.m_pos_y + m_state->m_global_offset_y;
	//graphics::drawRect(x, y,trophy.m_width,trophy.m_height, m_trophy_brush);
	graphics::drawRect(x, y, 1.0f, 1.0f, m_trophy_brush);

	// draw player
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();

	// draw blocks

	for (int i = 0; i < m_blocks.size(); i++)
	{
		drawBlock(i);
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		drawEnemy(i);
	}

	

}

void Level::init() {


if (m_name == "level1") {


		trophy.m_pos_x = -4.0f;
		trophy.m_pos_y = -5.5f;
		trophy.m_width = 1.0f;
		trophy.m_height = 1.0f;
		m_trophy_brush.outline_opacity = 0.0f;
		m_trophy_brush.texture = m_state->getFullAssetPath("trophy.png");

		m_blocks.push_back(Box(5, 10, 1, 1));
		m_blocks.push_back(Box(4, 10, 1, 1));
		m_blocks.push_back(Box(3, 10, 1, 1));
		m_blocks.push_back(Box(7, 8, 1, 1));
		m_blocks.push_back(Box(8, 8, 1, 1));
		m_blocks.push_back(Box(6, 6, 1, 1));
		m_blocks.push_back(Box(5, 6, 1, 1));
		m_blocks.push_back(Box(4, 6, 1, 1));
		m_blocks.push_back(Box(3, 6, 1, 1));
		m_blocks.push_back(Box(-1, 8, 1, 1));
		m_blocks.push_back(Box(-4, 6, 1, 1));
		m_blocks.push_back(Box(-6, 4, 1, 1));
		m_blocks.push_back(Box(-4, 2, 1, 1));
		m_blocks.push_back(Box(-3, 2, 1, 1));
		m_blocks.push_back(Box(-2, 2, 1, 1));
		m_blocks.push_back(Box(1, 0, 1, 1));
		m_blocks.push_back(Box(3, 2, 1, 1));
		m_blocks.push_back(Box(4, 2, 1, 1));
		m_blocks.push_back(Box(5, 1, 1, 1));
		m_blocks.push_back(Box(6, 1, 1, 1));
		m_blocks.push_back(Box(7, 0, 1, 1));
		m_blocks.push_back(Box(10, 3, 1, 1));

		m_blocks.push_back(Box(13, 1, 1, 1));
		m_blocks.push_back(Box(16, 0, 1, 1));
		m_blocks.push_back(Box(14, -2, 1, 1));
		m_blocks.push_back(Box(13, -2, 1, 1));
		m_blocks.push_back(Box(12, -2, 1, 1));
		m_blocks.push_back(Box(11, -4, 1, 1));

		m_blocks.push_back(Box(10, -5, 1, 1));
		m_blocks.push_back(Box(9, -6, 1, 1));
		m_blocks.push_back(Box(4, -4, 1, 1));
		m_blocks.push_back(Box(3, -4, 1, 1));
		m_blocks.push_back(Box(2, -4, 1, 1));

		m_blocks.push_back(Box(-2, -2, 1, 1));
		m_blocks.push_back(Box(-3, -4, 1, 1));
		m_blocks.push_back(Box(-4, -4, 1, 1));

		m_block_names.push_back("marble_packed1.png");
		m_block_names.push_back("marble_packed3.png");
		m_block_names.push_back("marble_packed2.png");
		m_block_names.push_back("marble_packed7.png");
		m_block_names.push_back("marble_packed5.png");
		m_block_names.push_back("marble_packed6.png");

		m_enemies.push_back(Box(-4, 9, 1, 1));
		m_enemies.push_back(Box(3, 9, 1, 1));
		m_enemies.push_back(Box(-8, -5, 1, 1));
		m_enemies.push_back(Box(0, -5, 1, 1));
		m_enemies.push_back(Box(8, -5, 1, 1));
		m_enemies.push_back(Box(-8, 1, 1, 1));
		m_enemies.push_back(Box(2, 1, 1, 1));
		m_enemies.push_back(Box(10, -1, 1, 1));
	}

	m_block_brush.outline_opacity = 0.0f;
	m_block_brush_debug.fill_opacity = 0.1f;
	m_enemy_brush.outline_opacity = 0.0f;
	m_enemy_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_block_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);
	SETCOLOR(m_enemy_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_enemy_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);



	


}

Level::Level(const std::string& name)
	: GameObject(name)
{
	m_brush_background.outline_opacity = 0.0f;
	if (name == "level1") {
		m_brush_background.texture = m_state->getFullAssetPath("background.png");
	}


}

Level::~Level()
{
	
	
}
