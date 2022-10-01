package inheritance;

/**
 * This program demonstrates inheritance.
 * @version 1.21 2022.10.2
 * @author Cynric
 */
public class ManagerTest{
    public static void main(String[] args){
        //construct a Manager object
        Manager boss = new Manager("Carl Cracker",80000,1987,12,15);
        boss.setBonus(5000);

        Employee[]  staff = new Employee[3];

        //fill the staff array with Manager and Employee objects

        staff[0] = boss;
        staff[1] = new Employee("Harry Hacker",50000,1989,10,1);
        staff[2] = new Employee("Tommy Tester",40000,1990,3,15);
        Manager Aboss = new Manager(null,0,1900,1,1 );
        Aboss = ((Manager)staff[0]).deepClone();
        Aboss.setBonus(100);
        //print out information about all Employee objects
        for (Employee e:staff)
            System.out.println("name=" + e.getName() + ",salary=" + e.getSalary());
        System.out.println("name=" + Aboss.getName() + ",salary=" + Aboss.getSalary());
        System.out.println("name=" + boss.getName() + ",salary=" + boss.getSalary());
    }

}
