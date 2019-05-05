/**
 *  Type assertions
 *  ===============
 *
 *  A similar Go snippet for it is:
 *
 *      package main
 *
 *      type ItemA struct{}
 *      type ItemB struct{}
 *
 *      func (ItemA) IsItem() {}
 *      func (ItemB) IsItem() {}
 *
 *      type ItemInterface interface {
 *          IsItem()
 *      }
 *
 *      type Item struct {
 *          Item ItemInterface
 *      }
 *
 *      func main() {
 *          a := ItemA{}
 *          item := Item{Item: a}
 *          _ = item.Item.(ItemA)
 *          _ = item.Item.(ItemB)
 *      }
 */

struct interface {
    virtual ~interface() = default;
};

struct foo : public interface {};
struct bar : public interface {};

int
main()
{
    foo a;
    interface& i = static_cast<interface &>(a);
    
    auto aa = dynamic_cast<foo &>(i);
    (void)aa;

    bar& b = dynamic_cast<bar &>(a); // std::bad_cast
    (void)b;

    return 0;
}
