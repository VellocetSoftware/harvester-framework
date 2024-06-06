#pragma once
#include "components_defines.h"

#if GDEXTENSION
#include <godot_cpp/classes/node.hpp>
#elif GODOT_MODULE
#include "scene/main/node.h"
#endif

/**
 * @class ComponentUtils
 *
 * @brief Utility class for working with components in Godot.
 *
 * The ComponentUtils class provides static methods for manipulating components attached to Godot nodes.
 * It allows you to get, add, and remove components from a node.
 */
class ComponentUtils : public RefCounted {
	GDCLASS(ComponentUtils, RefCounted);

protected:
	static void _bind_methods();

public:
	static void add_component(Object *p_object, Object *p_component);
	static Object *get_component(Object *p_object, const Variant &p_component_type, bool p_assert_exists = false);
	static Array get_components_recursive(Object *p_object, const Variant &p_component_type);
	static Array get_components(Object *p_object, const Variant &p_component_type);
	static Object *get_component_recursive(Object* p_object, const Variant& p_component_type, bool p_assert_exists = false);
	static void remove_component(Object *p_object, const String &p_component_name);
};
