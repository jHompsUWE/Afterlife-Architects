#pragma once

class StateTemplate
{
public:
    explicit StateTemplate() = default;
    virtual ~StateTemplate() = default;

    virtual bool init() = 0;

    virtual void Update() = 0;
    virtual void ScaledUpdate() = 0;
    virtual void LateUpdate() = 0;
};
