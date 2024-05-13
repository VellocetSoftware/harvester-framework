#include "component_utils.h"

#include "core/object/class_db.h"
#include "core/object/object.h"

#if GDEXTENSION
#elif GODOT_MODULE
#include "core/object/script_language.h"
#endif

void ComponentUtils::add_component(Object *p_object, Object *p_component) {
	ERR_FAIL_NULL(p_object);
	ERR_FAIL_NULL(p_component);
	Ref<Script> component_script = p_component->get_script();
	ERR_FAIL_COND(component_script.is_null());
	String component_name = component_script->get_global_name();
	Dictionary components;
	if (p_object->has_meta("_components")) {
		components = p_object->get_meta("_components");
	} else {
		p_object->set_meta("_components", components);
	}
	components[component_name] = p_component;
}

Object *ComponentUtils::get_component(Object *p_object, const Variant &p_component_type, bool p_assert_exists) {
	ERR_FAIL_NULL_V(p_object, nullptr);
	Ref component_script = Object::cast_to<Script>(p_component_type);

	ERR_FAIL_NULL_V(component_script, nullptr, "ComponentUtils.get_component: Component type is not valid.");
	String component_name = component_script->get_global_name();

	if (p_object->has_meta("_components")) {
		Dictionary components = p_object->get_meta("_components");
		//foreach value in components
		for (Object *component : components.values()) {
			Ref<Script> base_type = component->get_script_instance()->get_script();

			if (components.has(component_name)) {
				return cast_to<Object>(components[component_name]);
			}
			if (base_type->inherits_script(component_script)) {
				print_line(" ComponentUtils.get_component: Component " +
						component_name + " is a base class to " + component->get_script_instance()->get_script()->get_global_name()
						+ " on node " + String(Object::cast_to<Node>(p_object)->get_path()));
				return component;
			}
		}
	}

	ERR_FAIL_COND_V_MSG(p_assert_exists, nullptr, "ComponentUtils.get_component: Component " + component_name+ " does not exist on node " + String(Object::cast_to<Node>(p_object)->get_path()));

	return nullptr;
}


void ComponentUtils::remove_component(Object *p_object, const String &p_component_name) {
	ERR_FAIL_NULL(p_object);
	if (!p_object->has_meta("_components")) {
		return;
	}
	Dictionary components = p_object->get_meta("_components");
	if (components.has(p_component_name)) {
		components.erase(p_component_name);
	}
}

void ComponentUtils::_bind_methods() {
	ClassDB::bind_static_method("ComponentUtils", D_METHOD("add_component", "object", "component"), &ComponentUtils::add_component);
	ClassDB::bind_static_method("ComponentUtils", D_METHOD("get_component", "object", "component_name", "assert_exists"), &ComponentUtils::get_component, DEFVAL(false));
	ClassDB::bind_static_method("ComponentUtils", D_METHOD("remove_component", "object", "component_name"), &ComponentUtils::remove_component);
}
