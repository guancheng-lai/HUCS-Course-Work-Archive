/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package memory;
import javax.swing.JFrame;
import java.awt.Button;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JButton;
/**
 *
 * @author Laiman
 */
public class Memory extends JFrame{
    GameBoard gameBoard = new GameBoard();
    MenuBar menuBar = new MenuBar();
    
    public Memory(){
    setSize(800, 800);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    add(gameBoard);
    
    setupMenuBar();
    setVisible(true);
}
    public static void main(String[] args) {
        Memory memory = new Memory();
    }
    
    private void setupMenuBar(){
        Menu gameMenu = new Menu("Game");
        
        MenuItem menuItem_startOver = new MenuItem("Start Over");
        gameMenu.add(menuItem_startOver);
        menuItem_startOver.addActionListener(new ActionListener(){
        @Override
        public void actionPerformed(ActionEvent ev){
            initialize();
        }
    });
        
        MenuItem menuItem_showSolution = new MenuItem("Show Solution");
        gameMenu.add(menuItem_showSolution);
        menuItem_showSolution.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent ev){
                showSolution();
            }
        });
        
    menuBar.add(gameMenu);
    setMenuBar(menuBar);
    }
    
    private void initialize(){
        this.remove(gameBoard);
        gameBoard = new GameBoard();
        add(gameBoard);
        setVisible(true);
    }
    
    private void showSolution(){
        gameBoard.shouSolution();
    }
    
}
