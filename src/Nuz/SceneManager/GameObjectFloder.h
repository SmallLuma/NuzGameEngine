#pragma once
#include <map>
#include <memory>
#include <set>
#include <queue>
#include "../../../include/Nuz/SceneManager/Component.h"
#include "../../../include/Nuz/SceneManager/GameObject.h"

namespace Nuz_ {
	class GameObjectFloder final {
	public:
		enum ParentType { SCENE, GAMEOBJECT };
	private:
		std::map<std::string, std::shared_ptr<Nuz::IComponent>> m_mountName2component;
		std::set<std::shared_ptr<Nuz::IComponent>> m_allcomponent;

		std::map<std::string, std::shared_ptr<Nuz::IGameObject>> m_mountName2go;
		std::set<std::shared_ptr<Nuz::IGameObject>> m_allgo;

		ParentType m_parentType;
		std::weak_ptr<Nuz::IGameObject> m_goParent;
		std::weak_ptr<Nuz::IScene> m_scParent;

		std::queue<Nuz::IComponent*> m_unmountCompoTask;
		std::queue<Nuz::IGameObject*> m_unmountGOTask;
		void unmountGameObject_Really(Nuz::IGameObject*);
		void unmountComponent_Really(Nuz::IComponent*);
	public:
		inline GameObjectFloder() {};
		inline void SetParent(const std::shared_ptr<Nuz::IGameObject>& p) {
			m_goParent = p;
			m_parentType = ParentType::GAMEOBJECT;
		}
		inline void SetParent(const std::shared_ptr<Nuz::IScene>& p) {
			m_scParent = p;
			m_parentType = ParentType::SCENE;
		}

		inline ParentType GetParentType() { return m_parentType; }
		inline std::shared_ptr<Nuz::IGameObject> GetGOParent() { return m_goParent.lock(); }
		inline std::shared_ptr<Nuz::IScene> GetSCParent() { return m_scParent.lock(); }

		void MountComponent(const std::shared_ptr<Nuz::IComponent>&, const std::string& mountName = "");
		inline void UnmountComponent(const std::string& mountName)
		{
			if (m_mountName2component.count(mountName) == 1) {
				m_unmountCompoTask.push(m_mountName2component.at(mountName).get());
			}
		}
		inline void UnmountComponent(Nuz::IComponent* p) {
			m_unmountCompoTask.push(p);
		}
		inline std::shared_ptr<Nuz::IComponent> GetMountedComponent(const std::string& mountName) const
		{
			if (m_mountName2component.count(mountName) == 0) return std::shared_ptr<Nuz::IComponent>(nullptr);
			else return m_mountName2component.at(mountName);
		}

		void MountGameObject(const std::shared_ptr<Nuz::IGameObject>&, const std::string& mountName = "");
		inline void UnmountGameObject(const std::string& mountName)
		{
			if (m_mountName2go.count(mountName) == 1) {
				m_unmountGOTask.push(m_mountName2go.at(mountName).get());
			}
		}
		inline void UnmountGameObject(Nuz::IGameObject* p) {
			m_unmountGOTask.push(p);
		}
		std::shared_ptr<Nuz::IGameObject> GetMountedGameObject(const std::string& mountName) const;

		void OnUpdate();
		void OnDraw3D();
		void OnDraw2D();
		void OnDrawScreenReady();
		void OnDrawScreenFinished();
		void OnFadeSwitchOut(int timeLimited);
		void OnFadeSwitchOutUpdate(float finished);
		void OnFadeSwitchIn(int timeLimited);
		void OnFadeSwitchInUpdate(float finished);
	};
}