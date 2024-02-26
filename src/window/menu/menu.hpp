/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */

#ifndef WINDOW_MENU_MENU_HPP_
#define WINDOW_MENU_MENU_HPP_

#include "../../utils/ui/custom_components.h"
#include "../window_manager.h"

void show_menu(GLFWwindow *window) {

  ImGuiIO &io = ImGui::GetIO();

  if (WindowManager::mouse_state(window, GLFW_MOUSE_BUTTON_LEFT)) {
    io.MouseDown[0] = true;
    io.MouseClicked[0] = true;
    io.MouseClickedPos[0].x = io.MousePos.x;
    io.MouseClickedPos[0].x = io.MousePos.y;
  } else
    io.MouseDown[0] = false;

  glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, GLFW_FALSE);

  component::create_style();
  ImGui::SetNextWindowSize(ImVec2(500.0f, 350.0f), ImGuiCond_Once);
  ImGui::Begin(("Infestation - 6.5"), &settings::show_menu, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

  ImGui::BeginTabBar(("##tabs"), ImGuiTabBarFlags_None);
  ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 - 100, 50));

  ImGui::SetNextItemWidth(100);

  if (ImGui::BeginTabItem(("Aimbot"))) {
    ImGui::Text("Aimbot");
    ImGui::Checkbox("Enabled", &settings::aimbot::aimbot);

    ImGui::EndTabItem();
  }

  ImGui::SetNextItemWidth(100);

  if (ImGui::BeginTabItem(("ESP"))) {
    ImGui::Columns(2, NULL, false);
    ImGui::SetColumnOffset(1, 150);
    ImGui::Text("Player");
    ImGui::Checkbox("Enabled", &settings::visuals::player_esp);
    component::set_helper("Enable/Disable ESP");

    ImGui::NextColumn();

    ImGui::Checkbox("World", &settings::world::esp);
    component::set_helper("Enable/Disable World ESP");
    ImGui::Spacing();

    if (settings::world::esp) {

      ImGui::Checkbox("Weapons", &settings::world::weapon_esp);
      ImGui::SameLine();
      component::set_helper("Enable/Disable Weapons ESP");
      if (settings::world::weapon_esp) {
        ImGui::Checkbox("Weapon Icon", &settings::world::weapon_name);
        component::set_helper("Draw weapon name");
        ImGui::Checkbox("Weapon Distance", &settings::world::weapon_distance);
        component::set_helper("Draw distance to weapon");
        ImGui::Checkbox("Weapon Snap Lines", &settings::world::weapon_snaplines);
        component::set_helper("Draw lines to weapon");
      }

      ImGui::Spacing();
      ImGui::Checkbox("Grenades", &settings::world::grenade_esp);
      component::set_helper("Enable/Disable Grenades ESP");

      if (settings::world::grenade_esp) {
        ImGui::Checkbox("Grenade Name", &settings::world::grenade_warning);
        component::set_helper("Grenade projectile warning");
        ImGui::Checkbox("Grenade Name", &settings::world::grenade_name);
        component::set_helper("Grenade projectile name");
        ImGui::Checkbox("Grenade Distance", &settings::world::grenade_distance);
        component::set_helper("Grenade projectile distance");
        ImGui::Checkbox("Grenade Snap Lines", &settings::world::grenade_snaplines);
        component::set_helper("Draw lines to Grenade projectile");

        if (settings::misc::experimental_features) {

          ImGui::Checkbox("Grenade Timer", &settings::world::grenade_timer);
          component::set_helper("This is experimental feature", ImColor(211, 67, 18, 255), '!');

          ImGui::Checkbox("Grenade Trajectory", &settings::world::grenade_trajectory);
          component::set_helper("This is experimental feature", ImColor(211, 67, 18, 255), '!');
          component::color_picker("##nade_trail", settings::colors::grenade_trails);
        }
      }
    }

    ImGui::EndTabItem();
  }

  ImGui::SetNextItemWidth(100);

  if (ImGui::BeginTabItem("Misc")) {
    ImGui::Checkbox("Team-Check", &settings::misc::team_check);
    component::set_helper("Enable/Disable Team-Check");

    ImGui::Checkbox("Experimental", &settings::misc::experimental_features);
    component::set_helper("This enables using features under development, may also experience bugs and possible crashes", ImColor(211, 67, 18, 255), '!');

    if (ImGui::Button("Github"))
      ShellExecuteA(NULL, "open", "https://github.com/vsaint1/cs2-infestation", NULL, NULL, SW_SHOWNORMAL);

    ImGui::EndTabItem();
  }

  ImGui::EndTabBar();
  ImGui::End();
}

#endif // WINDOW_MENU_MENU_HPP_
