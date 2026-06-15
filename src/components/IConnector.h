#ifndef ICONNECTOR_H
#define ICONNECTOR_H

class IConnector
{
public:
	virtual ~IConnector() = default;

protected:
	virtual void connectUI() = 0;
	virtual void connectLogic() = 0;
};

#endif // !ICONNECTOR_H