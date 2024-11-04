import tkinter as tk
from tkinter import ttk
import random
import time
from typing import List, Tuple

class TwoPointersWaterContainerVisualizer:
    def __init__(self, root):
        self.root = root
        self.root.title("Visualizador de Contenedor de Agua (Two Pointers)")

        self.canvas_width = 800
        self.canvas_height = 400
        self.canvas = tk.Canvas(root, width=self.canvas_width, height=self.canvas_height, bg='white')
        self.canvas.pack(pady=20)

        self.control_frame = tk.Frame(root)
        self.control_frame.pack(pady=10)

        self.test_frame = tk.Frame(root)
        self.test_frame.pack(pady=5)

        tk.Label(self.test_frame, text="Casos de prueba:").pack(side=tk.LEFT, padx=5)
        self.test_cases = ["Manual", "10 elementos", "20 elementos", "30 elementos", 
                          "40 elementos", "50 elementos", "100 elementos", 
                          "1000 elementos", "10000 elementos"]
        self.test_var = tk.StringVar(value=self.test_cases[0])
        self.test_combo = ttk.Combobox(self.test_frame, textvariable=self.test_var, 
                                      values=self.test_cases, state="readonly")
        self.test_combo.pack(side=tk.LEFT, padx=5)

        self.test_combo.bind('<<ComboboxSelected>>', self.handle_test_case_selection)
        self.test_combo.bind('<Return>', self.handle_test_case_selection)
        self.test_combo.bind('<FocusOut>', self.handle_test_case_selection)

        tk.Label(self.control_frame, text="Ingrese alturas (separadas por comas):").pack(side=tk.LEFT, padx=5)
        self.height_entry = tk.Entry(self.control_frame, width=30)
        self.height_entry.pack(side=tk.LEFT, padx=5)
        self.height_entry.insert(0, "1,8,6,2,5,4,8,3,7")

        self.calc_button = tk.Button(self.control_frame, text="Calcular (Two Pointers)", command=self.calculate_and_draw)
        self.calc_button.pack(side=tk.LEFT, padx=5)

        self.info_frame = tk.Frame(root)
        self.info_frame.pack(pady=5)

        self.result_label = tk.Label(self.info_frame, text="")
        self.result_label.pack(side=tk.LEFT, padx=10)
        self.time_label = tk.Label(self.info_frame, text="")
        self.time_label.pack(side=tk.LEFT, padx=10)

        self.last_selection = "Manual"

    def generate_test_case(self, size: int) -> List[int]:
        try:
            return [random.randint(2, 100000) for _ in range(size)]
        except ValueError as e:
            print(f"Error generando caso de prueba: {e}")
            return [2] * size

    def handle_test_case_selection(self, event=None):
        try:
            selection = self.test_var.get()

            if selection == self.last_selection:
                return

            self.last_selection = selection

            if selection == "Manual":
                self.height_entry.config(state='normal')
                self.height_entry.delete(0, tk.END)
                self.height_entry.insert(0, "1,8,6,2,5,4,8,3,7")
                self.calculate_and_draw()
                return

            size = int(selection.split()[0])

            heights = self.generate_test_case(size)

            self.height_entry.config(state='normal')
            self.height_entry.delete(0, tk.END)
            self.height_entry.insert(0, ','.join(map(str, heights)))
            self.height_entry.config(state='disabled')

            self.root.update_idletasks()

            self.calculate_and_draw()

        except Exception as e:
            print(f"Error en handle_test_case_selection: {e}")
            self.result_label.config(text=f"Error: {str(e)}")

    def find_max_water_two_pointers(self, height: List[int]) -> Tuple[int, int, int]:
        if not height:
            return 0, 0, 0

        max_water = 0
        left = 0
        right = len(height) - 1
        best_left = left
        best_right = right

        while left < right:
            width = right - left
            h = min(height[left], height[right])
            water = width * h

            if water > max_water:
                max_water = water
                best_left = left
                best_right = right

            if height[left] < height[right]:
                left += 1
            else:
                right -= 1

        return max_water, best_left, best_right

    def draw_visualization(self, heights: List[int], max_water: int, best_left: int, best_right: int):
        try:
            self.canvas.delete("all")

            if not heights:
                return

            if len(heights) > 50:
                self.canvas.create_text(self.canvas_width/2, self.canvas_height/2,
                                      text=f"Visualización no disponible para {len(heights)} elementos.\n"
                                           f"El resultado ha sido calculado correctamente.",
                                      font=('Arial', 12))
                return

            max_height = max(heights)
            num_elements = len(heights)

            available_width = self.canvas_width - 150
            spacing = 5
            bar_width = min(35, (available_width - (num_elements - 1) * spacing) / num_elements)

            label_height = 40 if num_elements > 10 else 20

            scale_y = (self.canvas_height - 150 - label_height) / max_height

            margin_x = 75
            margin_y = self.canvas_height - 100 - label_height

            self.canvas.create_line(margin_x, margin_y, 
                                  self.canvas_width - margin_x/2, margin_y, 
                                  width=2, arrow=tk.LAST)

            self.canvas.create_line(margin_x, margin_y, 
                                  margin_x, 30, 
                                  width=2, arrow=tk.LAST)

            for i, height in enumerate(heights):
                x = margin_x + i * (bar_width + spacing)
                y = margin_y - height * scale_y

                color = 'red' if i == best_left or i == best_right else 'black'

                self.canvas.create_rectangle(x, margin_y, x + bar_width, y,
                                           fill=color, outline=color)

                if num_elements > 10:
                    self.canvas.create_text(x + bar_width/2, margin_y + 25,
                                          text=str(height),
                                          angle=90,
                                          anchor='e',
                                          font=('Arial', 8))
                else:
                    self.canvas.create_text(x + bar_width/2, margin_y + 15,
                                          text=str(height),
                                          anchor='n',
                                          font=('Arial', 10))

            x1 = margin_x + best_left * (bar_width + spacing)
            x2 = margin_x + best_right * (bar_width + spacing) + bar_width
            height_water = min(heights[best_left], heights[best_right])
            y_water = margin_y - height_water * scale_y

            self.canvas.create_rectangle(x1, margin_y, x2, y_water,
                                       fill='lightblue', stipple='gray50',
                                       outline='blue', width=1)

            legend_y = self.canvas_height - 30
            self.canvas.create_rectangle(margin_x, legend_y, margin_x + 20, legend_y + 10, 
                                       fill='red', outline='red')
            self.canvas.create_text(margin_x + 25, legend_y + 5, 
                                  text="Contenedores máximos", anchor='w')

            self.canvas.create_rectangle(margin_x + 200, legend_y, 
                                       margin_x + 220, legend_y + 10, 
                                       fill='lightblue', stipple='gray50')
            self.canvas.create_text(margin_x + 225, legend_y + 5, 
                                  text="Área de agua", anchor='w')

        except Exception as e:
            print(f"Error en draw_visualization: {e}")
            self.canvas.create_text(self.canvas_width/2, self.canvas_height/2,
                                  text=f"Error en la visualización: {str(e)}",
                                  font=('Arial', 12))

    def calculate_and_draw(self):
        """Calcula y visualiza los resultados"""
        import time
        try:
            heights = [int(x) for x in self.height_entry.get().split(',')]
            if not heights:
                self.result_label.config(text="Por favor ingrese valores válidos")
                return

            start_time = time.time()

            max_water, best_left, best_right = self.find_max_water_two_pointers(heights)

            elapsed_time = time.time() - start_time

            self.result_label.config(
                text=f"Máxima cantidad de agua: {max_water} (entre índices {best_left} y {best_right})")
            self.time_label.config(text=f"Tiempo de ejecución: {elapsed_time:.4f} segundos")

            self.draw_visualization(heights, max_water, best_left, best_right)

        except ValueError as e:
            self.result_label.config(text="Error: Ingrese números enteros separados por comas")
            self.time_label.config(text="")
        except Exception as e:
            self.result_label.config(text=f"Error: {str(e)}")
            self.time_label.config(text="")

if __name__ == "__main__":
    root = tk.Tk()
    app = TwoPointersWaterContainerVisualizer(root)
    root.mainloop()