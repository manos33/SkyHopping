#include "player.h"
#include "util.h"
#include <cmath>

void Player::update(float dt)
{
	float delta_time = dt / 1000.0f;

	movePlayer(dt);

	//falling off the world aka losing
	if (m_pos_y > 12.0f) {
		m_pos_x = 5.0f; m_pos_y = 9.0f;
	}

	if (graphics::getKeyState(graphics::SCANCODE_W))
		graphics::playSound(m_state->getFullAssetPath("cartoon-jump.wav"), 1.0f);

	// update offset for other game objects
	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	GameObject::update(dt);

}

void Player::draw()
{
	//when stopping our player stays still
	m_brush_player.texture = m_state->getFullAssetPath("creature-0.png");
	if (graphics::getKeyState(graphics::SCANCODE_A) or (graphics::getKeyState(graphics::SCANCODE_D))) {
		int sprite = (int)fmod(3000.0f - m_pos_x * 8.0f, m_sprites.size());
		m_brush_player.texture = m_sprites[sprite];
	}

	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 1.0f, 1.0f, m_brush_player);

	if (m_state->m_debugging)
		debugDraw();
}

void Player::init()
{
	
	m_pos_x = 5.0f;
	m_pos_y = 9.0f;

	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state->getFullAssetPath("creature-0.png");

	m_sprites.push_back(m_state->getFullAssetPath("creature-1.png"));
	m_sprites.push_back(m_state->getFullAssetPath("creature-2.png"));
	m_sprites.push_back(m_state->getFullAssetPath("creature-3.png"));


	// Adjust width for finer collision detection
	m_width = 0.7f;
}

void Player::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, m_width, m_height, debug_brush);

	char s[20];
	sprintf_s(s, "(%5.2f, %5.2f)", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(m_state->getCanvasWidth() * 0.5f - 0.4f, m_state->getCanvasHeight() * 0.5f - 0.6f, 0.15f, s, debug_brush);
}

void Player::movePlayer(float dt)
{
	if (m_state->m_debugging) {
		float delta_time = dt / 1000.0f;

		const float velocity = 10.0f;
		if (graphics::getKeyState(graphics::SCANCODE_A))
			m_pos_x -= velocity * delta_time;
		if (graphics::getKeyState(graphics::SCANCODE_D))
			m_pos_x += velocity * delta_time;

		if (graphics::getKeyState(graphics::SCANCODE_W))
			m_pos_y -= velocity * delta_time;
		if (graphics::getKeyState(graphics::SCANCODE_S))
			m_pos_y += velocity * delta_time;

		m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f / m_pos_x;
		m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f / m_pos_y;
	}
	else {
		float delta_time = dt / 600.0f;


		float move = 0.0f;
		if (graphics::getKeyState(graphics::SCANCODE_A))
			move -= 1.0f;
		if (graphics::getKeyState(graphics::SCANCODE_D))
			move = 1.0f;

		m_vx = std::min<float>(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
		m_vx = std::max<float>(-m_max_velocity, m_vx);

		// friction
		m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));

		// apply static friction threshold
		if (fabs(m_vx) < 0.01f)
			m_vx = 0.0f;

		// adjust horizontal position
		m_pos_x += m_vx * delta_time;

		// jump only when not in flight:
		if (m_vy == 0.0f)
			m_vy -= (graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f) * 0.02f;// not delta_time!! Burst 


		// add gravity
		m_vy += delta_time * m_gravity;

		// adjust vertical position
		m_pos_y += m_vy * delta_time;
	}
	

	
	
}

