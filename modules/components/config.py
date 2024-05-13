# This file is for building as a Godot module.
def can_build(env, platform):
    return True


def configure(env):
    pass


def get_doc_classes():
    return [
        "ComponentUtils",
    ]


def get_doc_path():
    return "addons/components/doc_classes"


def get_icons_path():
    return "addons/components/icons"
