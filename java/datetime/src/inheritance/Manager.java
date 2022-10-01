package inheritance;

public class Manager extends Employee   {
    private double bonus;
    /**
     * @param name the employee's name
     * @param salary the salary
     * @param year the hire year
     * @param month the hire month
     * @param day the hire day
     */
    public  Manager(String name,double salary,int year, int month, int day){
        super(name,salary,year,month,day);
        bonus = 0;
    }

    public double getSalary(){
        double baseSalary = super.getSalary();
        return baseSalary + bonus;
    }

    public  void setBonus(double b){
        bonus = b;
    }

    public Manager deepClone(){
        Manager isClone = new Manager(null,0,1900,1,1);
        isClone.name = super.name;
        isClone.salary = super.salary ;
        isClone.hireDay = super.hireDay;
        isClone.bonus =this.bonus;
        return isClone;
    }
}
