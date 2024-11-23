// This file added in headers queue
// File: "Sources.h"
#include "resource.h"
#include <map>
#include <vector>

namespace GOTHIC_ENGINE {

    std::map<std::string, int> keyNames;

    struct AnimKeyBind
    {
        std::string keyName;
        std::string aniName;
        oCNpc* target;

        int key() { return keyNames.at(keyName); }
        void play()
        {
            int ani = target->GetModel()->GetAniIDFromAniName(aniName.c_str());
            target->GetModel()->StartAni(ani, 0);
        };
    };
    std::vector<AnimKeyBind> animBinds;

    static zBOOL ConsoleEval(const zSTRING& s, zSTRING& msg) {

        if (!zcon->GetWorld()) {
            msg = "ERROR: no zCWorld registered to zcon !";
            return FALSE;
        };

        msg = "ok";

        zSTRING w1 = s.PickWord(1, " ", "\r\t ");
        zSTRING w2 = s.PickWord(2, " ", "\r\t ");
        zSTRING w3 = s.PickWord(3, " ", "\r\t ");
        zSTRING w4 = s.PickWord(4, " ", "\r\t ");
        w1.Upper();
        w2.Upper();
        w3.Upper();
        w4.Upper();

        if (w1 == "SET" && w2 == "KEYBIND" && !w3.IsEmpty() && !w4.IsEmpty())
        {
            AnimKeyBind newBind;
            newBind.keyName = w3;
            newBind.aniName = w4;

            if (player->GetFocusNpc())
                newBind.target = player->GetFocusNpc();
            else
                newBind.target = player;

            animBinds.push_back(newBind);
        }

        return FALSE;
    }

  void Game_Entry() {
  }
  
  void Game_Init() {

      keyNames.insert(std::pair<string, int>("N1", KEY_NUMPAD1));
      keyNames.insert(std::pair<string, int>("N2", KEY_NUMPAD2));
      keyNames.insert(std::pair<string, int>("N3", KEY_NUMPAD3));
      keyNames.insert(std::pair<string, int>("N4", KEY_NUMPAD4));
      keyNames.insert(std::pair<string, int>("N5", KEY_NUMPAD5));
      keyNames.insert(std::pair<string, int>("N6", KEY_NUMPAD6));
      keyNames.insert(std::pair<string, int>("N7", KEY_NUMPAD7));
      keyNames.insert(std::pair<string, int>("N8", KEY_NUMPAD8));
      keyNames.insert(std::pair<string, int>("N9", KEY_NUMPAD9));
      keyNames.insert(std::pair<string, int>("N0", KEY_NUMPAD0));

      keyNames.insert(std::pair<string, int>("Q", KEY_Q));
      keyNames.insert(std::pair<string, int>("W", KEY_W));
      keyNames.insert(std::pair<string, int>("E", KEY_E));
      keyNames.insert(std::pair<string, int>("R", KEY_R));
      keyNames.insert(std::pair<string, int>("T", KEY_T));
      keyNames.insert(std::pair<string, int>("Y", KEY_Y));
      keyNames.insert(std::pair<string, int>("U", KEY_U));
      keyNames.insert(std::pair<string, int>("I", KEY_I));
      keyNames.insert(std::pair<string, int>("O", KEY_O));
      keyNames.insert(std::pair<string, int>("P", KEY_P));
      keyNames.insert(std::pair<string, int>("LB", KEY_LBRACKET));
      keyNames.insert(std::pair<string, int>("RB", KEY_RBRACKET));
      keyNames.insert(std::pair<string, int>("A", KEY_A));
      keyNames.insert(std::pair<string, int>("S", KEY_S));
      keyNames.insert(std::pair<string, int>("D", KEY_D));
      keyNames.insert(std::pair<string, int>("F", KEY_F));
      keyNames.insert(std::pair<string, int>("G", KEY_G));
      keyNames.insert(std::pair<string, int>("H", KEY_H));
      keyNames.insert(std::pair<string, int>("J", KEY_J));
      keyNames.insert(std::pair<string, int>("K", KEY_K));
      keyNames.insert(std::pair<string, int>("L", KEY_L));
      keyNames.insert(std::pair<string, int>("SC", KEY_SEMICOLON));
      keyNames.insert(std::pair<string, int>("AP", KEY_APOSTROPHE));
      keyNames.insert(std::pair<string, int>("BS", KEY_BACKSLASH));
      keyNames.insert(std::pair<string, int>("Z", KEY_Z));
      keyNames.insert(std::pair<string, int>("X", KEY_X));
      keyNames.insert(std::pair<string, int>("C", KEY_C));
      keyNames.insert(std::pair<string, int>("V", KEY_V));
      keyNames.insert(std::pair<string, int>("B", KEY_B));
      keyNames.insert(std::pair<string, int>("N", KEY_N));
      keyNames.insert(std::pair<string, int>("M", KEY_M));
      keyNames.insert(std::pair<string, int>("CM", KEY_COMMA));
      keyNames.insert(std::pair<string, int>("PD", KEY_PERIOD));
      keyNames.insert(std::pair<string, int>("SL", KEY_SLASH));

      zcon->Register("SET KEYBIND", "");
      zcon->AddEvalFunc(ConsoleEval);
  }


  void Game_Exit() {
  }

  void Game_PreLoop() {
  }

  void Game_Loop() {

      for (auto it = animBinds.begin(); it != animBinds.end(); it++)
      {
          if (zinput->KeyToggled(it->key()))
              it->play();
      }
  }

  void Game_PostLoop() {
  }

  void Game_MenuLoop() {
  }

  // Information about current saving or loading world
  TSaveLoadGameInfo& SaveLoadGameInfo = UnionCore::SaveLoadGameInfo;

  void Game_SaveBegin() {
  }

  void Game_SaveEnd() {
  }

  void LoadBegin() {
  }

  void LoadEnd() {
  }

  void Game_LoadBegin_NewGame() {
    LoadBegin();
  }

  void Game_LoadEnd_NewGame() {
    LoadEnd();
  }

  void Game_LoadBegin_SaveGame() {
    LoadBegin();
  }

  void Game_LoadEnd_SaveGame() {
    LoadEnd();
  }

  void Game_LoadBegin_ChangeLevel() {
    LoadBegin();
  }

  void Game_LoadEnd_ChangeLevel() {
    LoadEnd();
  }

  void Game_LoadBegin_Trigger() {
  }
  
  void Game_LoadEnd_Trigger() {
  }
  
  void Game_Pause() {
  }
  
  void Game_Unpause() {
  }
  
  void Game_DefineExternals() {
  }

  void Game_ApplyOptions() {
  }

  /*
  Functions call order on Game initialization:
    - Game_Entry           * Gothic entry point
    - Game_DefineExternals * Define external script functions
    - Game_Init            * After DAT files init
  
  Functions call order on Change level:
    - Game_LoadBegin_Trigger     * Entry in trigger
    - Game_LoadEnd_Trigger       *
    - Game_Loop                  * Frame call window
    - Game_LoadBegin_ChangeLevel * Load begin
    - Game_SaveBegin             * Save previous level information
    - Game_SaveEnd               *
    - Game_LoadEnd_ChangeLevel   *
  
  Functions call order on Save game:
    - Game_Pause     * Open menu
    - Game_Unpause   * Click on save
    - Game_Loop      * Frame call window
    - Game_SaveBegin * Save begin
    - Game_SaveEnd   *
  
  Functions call order on Load game:
    - Game_Pause              * Open menu
    - Game_Unpause            * Click on load
    - Game_LoadBegin_SaveGame * Load begin
    - Game_LoadEnd_SaveGame   *
  */

#define AppDefault True
  CApplication* lpApplication = !CHECK_THIS_ENGINE ? Null : CApplication::CreateRefApplication(
    Enabled( AppDefault ) Game_Entry,
    Enabled( AppDefault ) Game_Init,
    Enabled( AppDefault ) Game_Exit,
    Enabled( AppDefault ) Game_PreLoop,
    Enabled( AppDefault ) Game_Loop,
    Enabled( AppDefault ) Game_PostLoop,
    Enabled( AppDefault ) Game_MenuLoop,
    Enabled( AppDefault ) Game_SaveBegin,
    Enabled( AppDefault ) Game_SaveEnd,
    Enabled( AppDefault ) Game_LoadBegin_NewGame,
    Enabled( AppDefault ) Game_LoadEnd_NewGame,
    Enabled( AppDefault ) Game_LoadBegin_SaveGame,
    Enabled( AppDefault ) Game_LoadEnd_SaveGame,
    Enabled( AppDefault ) Game_LoadBegin_ChangeLevel,
    Enabled( AppDefault ) Game_LoadEnd_ChangeLevel,
    Enabled( AppDefault ) Game_LoadBegin_Trigger,
    Enabled( AppDefault ) Game_LoadEnd_Trigger,
    Enabled( AppDefault ) Game_Pause,
    Enabled( AppDefault ) Game_Unpause,
    Enabled( AppDefault ) Game_DefineExternals,
    Enabled( AppDefault ) Game_ApplyOptions
  );
}